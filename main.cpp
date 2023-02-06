#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include <iostream>
#include <vector>

struct Armor {
 	Name name;
	AC ac{};
};

struct Helmet {
 	Name name;
	AC ac{};
};

struct Potion {
	Name name;
};

struct Scroll {
	Name name;
};

struct Weapon {
	Name name;
	Damage dmg{};
};


struct Player{
	std::string name;
	AC ac{10, BodyLocation::ALL};
};

struct Enemy{
	Name name;
};

struct Npc{
	Hp hp{5};
};

struct DefaultWeapon {
	std::string name;
	Damage dmg{};
};

struct CustomWeapon { // is not Damagable but still counts as AttackStrategable because have custom AttackStrategy_
	Name name;
	std::vector<DefaultWeapon> others{
		DefaultWeapon{Name{"Light weapon"}, Damage{10}},
		DefaultWeapon{Name{"Medium weapon"}, Damage{20}}
	};
};

template <> struct AttackStrategy_<CustomWeapon> {
	// bool operator()(Damagingable auto& obj, Object* owner, Object* target) { // when got Damagable property
	// 	return true;
	// }

	bool operator()(auto& obj, Object* owner, Object* target) { // CustomWeapon is not Damagable but can be
		if (not owner) {
			return false;
		}
		auto *suspect = Whom(owner, target);
		auto hp_opt = suspect->get(Parameter::Hp);

		if (hp_opt) {
			auto* hp_ptr = std::get<int*const>(hp_opt.value());

			if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) { // when got Damagable property
				*hp_ptr -= obj.dmg.value();
			}

			for (auto& other : obj.others) {
				operator()(other, hp_ptr);
			}
		}
		return true;
	}

	bool operator()(Damagingable auto& obj, auto* hp_ptr) { // sub attacks
		*hp_ptr -= obj.dmg.value();

		std::cout << "\t\t for " << obj.dmg.value() << " dmg";
		std::cout << " with " << static_cast<std::string>(obj.name) << '\n';
		return true;
	}
};

int main() {
	auto print_hp = [](const auto& value) {
		auto* value_ptr = std::get<int*const>(value);
		std::cout << "(Hp: " << *value_ptr << ")\n";
		return std::optional{value_ptr};
	};
	auto print_cure_hp = [](const auto& value) {
		auto* value_ptr = std::get<int*const>(value);
		std::cout << "(Cure Hp: " << *value_ptr << ")\n";
		return std::optional{value_ptr};
	};
	auto print_ac = [](const auto& value) {
		auto value_ref = std::get<std::reference_wrapper<AC>>(value);
		std::cout << "(Ac: " << value_ref.get().value() << ") ";
		return std::optional{value_ref};
	};
	auto print_dmg = [](const auto& value) {
		auto* value_ptr = std::get<int*const>(value);
		std::cout << "(Damage: " << *value_ptr << ")\n";
		return std::optional{value_ptr};
	};
	auto print_person = [&](auto&& person){
		std::cout << person.name();
		if (auto alive_opt = person.alive()) {
			if (alive_opt.value()) {
				std::cout << " [alive] ";
			} else {
				std::cout << " [dead] ";
			}
		} else {
			std::cout << " [unliving] ";
		}
		person.get(Parameter::Ac).and_then(print_ac);
		person.get(Parameter::Hp).and_then(print_hp);
	};

	std::vector< Object > backpack;
	
	auto sword = Damaging<Weapon>{ Name{"SWORD"}, Damage{16}};
	auto giant_sword = Weapon{ Name{"GIANT_SWORD"}, Damage{32}};
	backpack.emplace_back( sword );
	backpack.emplace_back( giant_sword );

	auto custom = CustomWeapon{ Name{"Custom_SWORD"}/*, Damage{32}*/};
	auto default_battle = Damaging<DefaultWeapon>{ Name{"Custom_BATTLE_SWORD"}, Damage{32}};
	backpack.emplace_back( custom );
	backpack.emplace_back( Damaging<CustomWeapon>{ Name{"new Custom_SWORD"}, Damage{32}} );
	backpack.emplace_back( default_battle );

	// second Living and Cure will be ignored
	auto gustav = Living<Healing<Living<Healing<Weapon>>>>{ Name{"GUSTAV_INTELIGENT_SWORD"}, Hp{20}/*, Hp{20}, Damage{32}*/};
	gustav.name = Name{"Franco The Inteligent Sword"};
	gustav.hp = Hp{75};
	gustav.cureHp = Hp{30};
	gustav.dmg = Damage{100};
	Object gustav_obj{gustav};

	std::cout << gustav_obj.name() << '\n';
	gustav_obj.get(Parameter::Hp).and_then(print_hp);
	gustav_obj.get(Parameter::CureHp).and_then(print_cure_hp);
	gustav_obj.get(Parameter::Ac).and_then(print_ac);
	gustav_obj.get(Parameter::Damage).and_then(print_dmg);
	std::cout << '\n';

	backpack.push_back( std::move(gustav_obj) );

	auto gustav_2 = Living<Healing<Living<Healing<Weapon>>>>( Name{"GUSTAV_INTELIGENT_SWORD"},/*hp*/ Hp{20},/*cureHp*/ Hp{30}, Damage{32});
	if (gustav_2.hp != Hp{20}) throw;
	if (gustav_2.cureHp != Hp{30}) throw;
	static_assert(std::is_same_v< decltype(gustav_2), Living<Healing<Weapon>> >);
	backpack.emplace_back( gustav_2 );

	backpack.emplace_back( Armor{ Name{"CHAIN_MAIL"}, AC{8, BodyLocation::Body}});
	backpack.emplace_back( Protecting<Armor>{ Name{"HALF_PLATE"}, AC{12}});
	backpack.emplace_back( Helmet{ Name{"VIKING_HELM"}, AC{2, BodyLocation::Head} });
	backpack.emplace_back( Damaging<Helmet>( Name{"BATTLE_HELM"} , Damage{10}, AC{4, BodyLocation::Head}));
	backpack.emplace_back( Healing<Potion>( Name{"HEALING_POTION"}, Hp{20}));
	backpack.emplace_back( Healing<Potion>{ Name{"SMALL_HEALING_POTION"}, Hp{10}});
	backpack.emplace_back( Protecting<Potion>( Name{"SHIELD_POTION"}, AC{4, BodyLocation::Internal}));
	backpack.emplace_back( Scroll{ Name{"USELESS_SCROLL"} });
	backpack.emplace_back( Scroll{ Name{"EMPTY_SCROLL"} });
	backpack.emplace_back( Damaging<Scroll>( Name{"SLEEP_SCROLL"}, Damage{0} ));
	backpack.emplace_back( Damaging<Healing<Scroll>>( Name{"VAMPIRIC_TOUCH_SCROLL"}, Damage{30}, Hp{15}));

	Object player( Living<Player>{Name{"Knight"}, Hp{100}} );
	print_person(player);
	Object enemy( Living<Enemy>{Name{"Ogr"}, Hp{180}} );
	print_person(enemy);
	Object enemy_2( Enemy{Name{"Ogr 2"}} );
	print_person(enemy_2);
	std::cout << "\n\n";

	std::cout << "Items I can attack with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if ( item->can_attack ) {
			std::cout << player.name() << " attack " << enemy.name() << " with " << item->name();
			if (auto dmg_opt = item->get(Parameter::Damage)) {
				auto* value_ptr = std::get<int*const>(dmg_opt.value());
				std::cout << " for " << *value_ptr << " dmg";
			}
			std::cout << '\n';
			auto result = item->attack(&player, &enemy);
			if (not result) {
				std::cout << " attack miss ";
			}
			print_person(enemy);
		}
	}
	std::cout << '\n';

	std::cout << "Items I can defend with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if ( item->defend(&player/*, &player*/) ) {
			std::cout << player.name() << " defend self with " << item->name();
			if (auto ac_opt = item->get(Parameter::Ac)) {
				const AC& value_ref = std::get<std::reference_wrapper<AC>>(ac_opt.value());
				std::cout << " for " << value_ref.value() << " AC";
			}
			std::cout << '\n';
			print_person(player);
		}
	}
	std::cout << '\n';

	std::cout << "Items I can heal with:" << '\n';
	for ( auto item = backpack.begin(); item != backpack.end(); ++item ) {
		if ( item->heal(100, &player/*, &player*/) ) {
			std::cout << player.name() << " heal self with " << item->name();
			if (auto cureHp_opt = item->get(Parameter::CureHp)) {
				auto* value_ptr = std::get<int*const>(cureHp_opt.value());
				std::cout << " for " << *value_ptr << " Hp";
			}
			std::cout << '\n';

			print_person(player);
		}
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
	print_person(Object(gustav));
	print_person(enemy);
	print_person(enemy_2); // enemy_2 dont have hp
	std::cout << '\n';

	return 0;
}
