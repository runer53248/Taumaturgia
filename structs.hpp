#pragma once
#include <iostream>

struct Armor {
 	Name name;
	ArmorClass ac{};
};

struct Helmet {
 	Name name;
	ArmorClass ac{};
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

struct NoNameWeapon {
	Damage dmg{};
};

struct Player{
	std::string name; // string used as name
	ArmorClassContainer armorWear{10};
};

struct Enemy{
	Name name;
};

struct Npc{ // don't have name 
	Health hp{5};
};

struct DefaultWeapon {
	std::string name; // string used as name
	Damage dmg{};
};

struct CustomWeapon { // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
	Name name;
	std::vector<DefaultWeapon> others{ // will be used in AttackStrategy_<CustomWeapon>
		DefaultWeapon{Name{"Light weapon"}, Damage{10}},
		DefaultWeapon{Name{"Medium weapon"}, Damage{20}}
	};
};

template <> struct AttackStrategy_<CustomWeapon> {
	// bool operator()(Damagingable auto& obj, Object* owner, Object* target) { // when got Damagingable property
	// 	return true;
	// }

	bool operator()(auto& obj, Object* owner, Object* target) const { // CustomWeapon is not Damagingable but can became one
		if (not owner) {
			return false;
		}
		auto *suspect = Whom(owner, target);
		auto hp_opt = getOpt<Parameter::Health>(*suspect);
		if (hp_opt) {
			Health& hp = hp_opt.value();
			if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) { // when got Damagingable property
				hp.removeHealth(obj.dmg.value());
			}

			for (auto& other : obj.others) {
				hp.removeHealth(other.dmg.value());

				subAttacks(other);
			}
		}
		return true;
	}

	bool subAttacks(Damagingable auto& obj) const {
		std::cout << "\t\t " << obj << "\n";
		return true;
	}
};
