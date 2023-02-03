#include "ObjectActions.hpp"
#include <vector>

struct Player{
	std::string name;
};

struct Enemy{
	std::string name;
};

struct Npc{
	std::string name;
	Hp hp{5};
};

struct DefaultWeapon {
	std::string name;
	Damage dmg{};
};

int main() {
	static_assert(std::is_same_v< GetStrategy<Accept>, GetStrategy<Npc> >); // Npc will use default Get strategy - Livable concept pass
	static_assert(std::is_same_v< GetStrategy<Accept>, GetStrategy<Living<Player>> >); // Player will use default Get strategy - Livable concept pass

	static_assert(std::is_same_v< GetStrategy<Living_<Player>>, GetStrategy<Living<Player>> >); // Livable traits added
	static_assert(std::is_same_v< GetStrategy<Npc>, GetStrategy<Living<Npc>> >);// Livable concept pass

	static_assert(not std::is_same_v< AttackStrategy<Accept>, AttackStrategy<Player> >);// Livable concept pass

	static_assert(std::is_same_v< GetStrategy<Battle<Living<Cure<Player>>>>, GetStrategy<Battle<Living<Cure<Player>>>> >);
	static_assert(std::is_same_v< GetStrategy<Battle<Living<Cure<Player>>>>, GetStrategy<Battle<Battle<Living<Living<Cure<Living<Player>>>>>>> >);
	static_assert(std::is_same_v< GetStrategy<Battle<Npc>>, GetStrategy<Battle<Living<Npc>>> >);

	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<Cure<Weapon>> >);
	static_assert(std::is_same_v< HealStrategy<Accept>, HealStrategy<Cure<Weapon>> >);
	static_assert(not std::is_same_v< HealStrategy<Accept>, HealStrategy<Weapon> >);
	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<DefaultWeapon> >);
	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<Cure<DefaultWeapon>> >);

	static_assert(std::is_same_v< DefaultWeapon, Battle<Battle<DefaultWeapon>> >);
	static_assert(not std::is_same_v< Enemy, Battle<Enemy> >);
	static_assert(std::is_same_v< Battle<Enemy>, Battle<Battle<Enemy>> >);

	std::vector< Object > backpack;
	
	auto sword = Battle<Weapon>{ "SWORD", Damage{16}};
	auto giant_sword = Weapon{ "GIANT_SWORD", Damage{32}};
	static_assert(sizeof(sword) == sizeof(giant_sword));
	backpack.emplace_back( sword );
	backpack.emplace_back( giant_sword );

	auto custom = DefaultWeapon{ "Custom_SWORD", Damage{32}};
	auto custom_battle = Battle<DefaultWeapon>{ "Custom_BATTLE_SWORD", Damage{32}};
	static_assert(sizeof(custom) == sizeof(custom_battle));
	backpack.emplace_back( custom );
	backpack.emplace_back( custom_battle );
	
	// secon Living and Cure will be ignored
	auto gustav = Living<Cure<Living<Cure<Weapon>>>>( "GUSTAV_INTELIGENT_SWORD", Hp{20}/*, Hp{20}, Damage{32}*/);
	gustav.name = "Franco The Inteligent Sword";
	gustav.hp = Hp{75};
	gustav.cureHp = Hp{30};
	gustav.dmg = Damage{100};
	backpack.emplace_back( gustav );

	auto gustav_2 = Living<Cure<Living<Cure<Weapon>>>>( "GUSTAV_INTELIGENT_SWORD", Hp{20}/*, Hp{20}*/, Damage{32});
	backpack.emplace_back( gustav_2 );

	backpack.emplace_back( Armor{ "CHAIN_MAIL", AC{8}});
	backpack.emplace_back( Protection<Armor>{ "HALF_PLATE", AC{12}});
	backpack.emplace_back( Helmet{ "VIKING_HELM", AC{2} });
	backpack.emplace_back( Battle<Helmet>( "BATTLE_HELM" , Damage{10}, AC{2}));
	backpack.emplace_back( Cure<Potion>( "HEALING_POTION", Hp{20}));
	backpack.emplace_back( Cure<Potion>( "SMALL_HEALING_POTION", Hp{10}));
	backpack.emplace_back( Protection<Potion>( "SHIELD_POTION", AC{4}));
	backpack.emplace_back( Scroll{ "USELESS_SCROLL" });
	backpack.emplace_back( Scroll{ "EMPTY_SCROLL" });
	backpack.emplace_back( Battle<Scroll>( "SLEEP_SCROLL", Damage{0} ));
	backpack.emplace_back( Battle<Cure<Scroll>>( "VAMPIRIC_TOUCH_SCROLL", Damage{30}, Hp{15}));

	static_assert(sizeof(Battle<Scroll>) == sizeof(Battle<Battle<Scroll>>));
	static_assert(sizeof(Weapon) == sizeof(Battle<Battle<Weapon>>));

	Object player( Living<Player>("Knight", Hp{100}) );
	Object enemy( Living<Enemy>("Ogr", Hp{50}) );
	Object enemy_2( Enemy{"Ogr 2"} );

	std::cout << '\n';
	std::cout << "Items I can attack with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		// caled from hidden friend
		if ( attack(*item, &player, &enemy) ) {}
	}
	std::cout << '\n';

	std::cout << "Items I can defend with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		// caled from hidden friend
		if ( defend(*item, &player/*, &player*/) ) {}
	}
	std::cout << '\n';

	std::cout << "Items I can heal with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		// called by method
		if ( item->heal(100, &player/*, &player*/) ) {}
	}
	std::cout << '\n';

	Object franco{gustav};
	franco.attack(&franco, &enemy);
	attack(franco, &franco, &enemy);

	Object npc( Npc{"Npc"} );
	franco.defend(&npc); // npc can't defend with franco - ignored
	franco.attack(&npc); // npc hit himself with franco

	std::cout << '\n';
	npc.get(Parameter::Hp);
	std::cout << '\n';
	player.get(Parameter::Hp);
	std::cout << '\n';
	Object(gustav).get(Parameter::Hp);
	std::cout << '\n';
	get(enemy, Parameter::Hp);
	std::cout << '\n';

	get(enemy_2, Parameter::Hp); // enemy_2 dont have hp
	std::cout << '\n';

   return 0;     
}
