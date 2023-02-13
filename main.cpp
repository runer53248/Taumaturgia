#include "Object/Object.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"
#include <iostream>
#include <vector>

#include "structs.hpp"
#include "preety_print.hpp"

int main() {
	std::vector<Object> backpack;
	
	backpack.emplace_back( Damaging<Weapon>{ Name{"SWORD"}, Damage{16}} );
	backpack.emplace_back( Weapon{ Name{"GIANT_SWORD"}, Damage{32}} );
	backpack.emplace_back( CustomWeapon{ Name{"Custom_SWORD"}} );
	backpack.emplace_back( Damaging<CustomWeapon>{ Name{"New_Custom_SWORD"}, Damage{32}} ); // became Damagingable - custom AttackStrategy_ will handle it
	backpack.emplace_back( Damaging<DefaultWeapon>{ Name{"Default_BATTLE_SWORD"}, Damage{32}} );

	// second Living and Healing will be ignored
	auto gustav = Living<Healing<Living<Healing<Weapon>>>>{ Name{"GUSTAV_INTELIGENT_SWORD"},/*hp*/ Hp{20}};
	static_assert(std::is_same_v< decltype(gustav), Living<Healing<Weapon>> >);
	gustav.name = Name{"Franco The Inteligent Sword"};
	gustav.hp = Hp{75};
	gustav.cureHp = Hp{30};
	gustav.dmg = Damage{100, AttackEffect::Stun};
	Object gustav_obj{gustav};

	std::cout << gustav_obj.name() << '\n';
	[](const auto& obj) { // get const version
		get(obj, Parameter::Hp).and_then(print_hp);
		get(obj, Parameter::CureHp).and_then(print_cure_hp);
		get(obj, Parameter::Ac).and_then(print_ac);
		get(obj, Parameter::Damage).and_then(print_dmg);
	} (gustav_obj);

	get(gustav_obj, Parameter::Hp).and_then(print_hp); // get non-const version
	get(gustav_obj, Parameter::CureHp).and_then(print_cure_hp);
	get(gustav_obj, Parameter::Ac).and_then(print_ac); // ignored - object dont have Ac
	get<const Object>(gustav_obj, Parameter::Damage).and_then(print_dmg); // force get const version
	std::cout << '\n';

	backpack.push_back( std::move(gustav_obj) );

	auto gustav_2 = Living<Healing<Living<Healing<Weapon>>>>( Name{"GUSTAV_INTELIGENT_SWORD"},/*hp*/ Hp{20},/*cureHp*/ Hp{30}, Damage{32});
	static_assert(std::is_same_v< decltype(gustav_2), Living<Healing<Weapon>> >);
	backpack.emplace_back( gustav_2 );

	backpack.emplace_back( Armor{ Name{"CHAIN_MAIL"}, AC{8, BodyLocation::Body}});
	backpack.emplace_back( Protecting<Armor>{ Name{"HALF_PLATE"}, AC{12}});
	backpack.emplace_back( Damaging<Helmet>( Name{"BATTLE_HELM"} , Damage{10}, AC{4, BodyLocation::Head}));
	backpack.emplace_back( Helmet{ Name{"VIKING_HELM"}, AC{2, BodyLocation::Head} });
	backpack.emplace_back( Healing<Potion>( Name{"HEALING_POTION"}, Hp{20}));
	backpack.emplace_back( Healing<Potion>{ Name{"SMALL_HEALING_POTION"}, Hp{10}});
	backpack.emplace_back( Protecting<Potion>( Name{"SHIELD_POTION"}, AC{4, BodyLocation::Internal}));
	backpack.emplace_back( Scroll{ Name{"USELESS_SCROLL"} });
	backpack.emplace_back( Scroll{ Name{"EMPTY_SCROLL"} });
	backpack.emplace_back( Damaging<Scroll>( Name{"SLEEP_SCROLL"}, Damage{0, AttackEffect::Sleep} )); //TODO add effects
	backpack.emplace_back( Damaging<Healing<Scroll>>( Name{"VAMPIRIC_TOUCH_SCROLL"}, Damage{30, AttackEffect::Devour}, Hp{15}));

	Object player( Living<Player>{Name{"Knight"}, Hp{100}} );
	print_person(player);
	Object enemy( Living<Enemy>{Name{"Ogr"}, Hp{180}} );
	print_person(enemy);
	Object enemy_2( Enemy{Name{"Ogr 2"}} );
	print_person(enemy_2);
	std::cout << "\n\n";

	std::cout << "Items I can attack with:\n\n";
	for (const auto& item : backpack) {
		if (not item.can_attack) {
			continue;
		}
		std::cout << player.name() << " attack " << enemy.name() << " with " << item.name();
		// AttackEffect effect{};
		if (auto dmg_opt = get(item, Parameter::Damage)) {
			const Damage& damage = Get<Damage>(dmg_opt.value());
			std::cout << " for " << damage.value() << " dmg";
			// if (damage.effect() != AttackEffect::None) {
			// 	effect = damage.effect();
			// }
		}
		std::cout << '\n';
		if (not item.attack(&player, &enemy)) {
			std::cout << " attack miss "; // unusable yet
		} 
		// else if (effect != AttackEffect::None) {
		// 	if(auto hp_opt = get(enemy, Parameter::Hp)) {
		// 		Hp& hp = Get<Hp>(hp_opt.value());
		// 		hp.effect() = effect;
		// 	}
		// }
		print_person(enemy);
	}
	std::cout << '\n';

	std::cout << "Items I can defend with:\n\n";
	for (const auto& item : backpack) {
		if (not item.can_defend) {
			continue;
		}
		if (not item.defend(&player/*, &player*/)) {
			std::cout << " protection broken "; // unusable yet
		}

		std::cout << player.name() << " defend self with " << item.name();
		if (auto ac_opt = get(item, Parameter::Ac)) {
			const AC& ac = Get<AC>(ac_opt.value());
			std::cout << " for " << ac.value() << " AC";
		}
		std::cout << '\n';
		print_person(player);
	}
	std::cout << '\n';

	std::cout << "Items I can heal with:\n\n";
	for (const auto& item : backpack) {
		if (not item.can_heal) {
			continue;
		}
		if (not item.heal(&player, &player)) {
			std::cout << " healing don't work "; // unusable yet
		}

		std::cout << player.name() << " heal self with " << item.name();
		if (auto cureHp_opt = get(item, Parameter::CureHp)) {
			const Hp& cureHp = Get<Hp>(cureHp_opt.value());
			std::cout << " for " << cureHp.value() << " Hp";
		}
		std::cout << '\n';
		print_person(player);
	}
	std::cout << '\n';

	Object franco{gustav};

	print_person(enemy);
	franco.attack(&franco, &enemy);
	print_person(enemy);

	Object npc( Naming<Npc>{Name{"Npc"}} );
	franco.defend(&npc); // npc can't defend with franco - ignored

	print_person(npc);
	franco.attack(&npc); // npc hit himself with franco
	print_person(npc);

	print_person(player);
	print_person(enemy);
	print_person(enemy_2); // enemy_2 dont have hp
	std::cout << '\n';

	Object{Healing<Potion>{ Name{"HEALING_POTION"}, Hp{100}}}.heal(&npc);
	print_person(npc);

	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if (item->can_alive) {
			print_person(*item);
		}
	}
	return 0;
}
