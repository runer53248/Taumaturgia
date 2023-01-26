#include "ObjectActions.hpp"
#include <vector>

struct Player{
	std::string name;
};

struct Enemy{
	std::string name;
};

struct CustomWeapon {
	std::string name;
	Damage dmg{};
};

int main() {

	static_assert(std::is_same_v<CustomWeapon, Battle<CustomWeapon>>);
	static_assert(std::is_same_v<CustomWeapon, Battle<Battle<CustomWeapon>>>);
	static_assert(not std::is_same_v<Enemy, Battle<Enemy>>);
	static_assert(std::is_same_v<Battle<Enemy>, Battle<Battle<Enemy>>>);

	std::vector< Object > backpack;
	
	auto sword = Battle<Weapon>( "SWORD", Damage{16});
	auto giant_sword = Weapon( "GIANT_SWORD", Damage{32});
	static_assert(sizeof(sword) == sizeof(giant_sword));
	backpack.emplace_back( sword );
	backpack.emplace_back( giant_sword );

	auto custom_bad = CustomWeapon( "Custom_SWORD_bad", Damage{32});;
	auto custom_good = Battle<CustomWeapon>( "Custom_SWORD_good", Damage{32});
	static_assert(sizeof(custom_bad) == sizeof(custom_good));
	backpack.emplace_back( custom_bad ); // will not attack with this
	backpack.emplace_back( custom_good ); // now will attack
	
	auto gustav = Living<Cure<Living<Cure<Weapon>>>>( "GUSTAV_INTELIGENT_SWORD", Hp{20}/*, Hp{20}, Damage{32}*/);
	gustav.name = "Franco The Inteligent Sword";
	gustav.hp = Hp{75};
	gustav.cureHp = Hp{30};
	gustav.dmg = Damage{100};
	backpack.emplace_back( gustav );

	auto gustav_2 = Living<Cure<Living<Cure<Weapon>>>>( "GUSTAV_INTELIGENT_SWORD", Hp{20}/*, Hp{20}*/, Damage{32});
	backpack.emplace_back( gustav_2 );

	backpack.emplace_back( Armor( "CHAIN_MAIL", AC{8}));
	backpack.emplace_back( Protection<Armor>( "HALF_PLATE", AC{12}));
	backpack.emplace_back( Helmet( "VIKING_HELM", AC{2} ));
	backpack.emplace_back( Battle<Helmet>( "BATTLE_HELM" , Damage{10}, AC{2}));
	backpack.emplace_back( Cure<Potion>( "HEALING_POTION", Hp{20}));
	backpack.emplace_back( Cure<Potion>( "SMALL_HEALING_POTION", Hp{10}));
	backpack.emplace_back( Protection<Potion>( "SHIELD_POTION", AC{4}));
	backpack.emplace_back( Battle<Scroll>( "SLEEP_SCROLL", Damage{0} ));
	backpack.emplace_back( Battle<Cure<Scroll>>( "VAMPIRIC_TOUCH_SCROLL", Damage{30}, Hp{15}));

	static_assert(sizeof(Battle<Scroll>) == sizeof(Battle<Battle<Scroll>>));
	static_assert(sizeof(Weapon) == sizeof(Battle<Battle<Weapon>>));

	Object player( Living<Player>("Knight", Hp{100}) );
	Object enemy( Living<Enemy>("Ogr", Hp{50}) );

	std::cout << '\n';
	std::cout << "Items I can attack with:" << '\n';
	for( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if( attack(*item, &player, &enemy) ) {}
		// if( item->attack(&player, &enemy) ) {}
	}
	std::cout << '\n';

	std::cout << "Items I can defend with:" << '\n';
	for( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if( defend(*item, &player/*, &player*/) ) {}
		// if( item->defend(&player/*, &player*/) ) {}
	}
	std::cout << '\n';

	std::cout << "Items I can heal with:" << '\n';
	for( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		// if( heal(*item, 100, &player, &player) ) {}
		if( item->heal(100, &player/*, &player*/) ) {}
	}
	std::cout << '\n';

	Object franco{gustav};
	franco.attack(&franco, &enemy);
	franco.attack(&franco, &enemy);

	Object npc( Living<Player>("Npc", Hp{5}) );
	franco.defend(&npc); // npc can't defend with franco - ignored
	franco.attack(&npc); // npc hit himself with franco

	player.get(Parameter::Hp);
	std::cout << '\n';
	Object(gustav).get(Parameter::Hp);
	std::cout << '\n';
	get(enemy, Parameter::Hp);
	std::cout << '\n';

   return 0;     
}
