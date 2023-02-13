#pragma once

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
	std::string name; // string used as name
	AC ac{10, BodyLocation::ALL};
};

struct Enemy{
	Name name;
};

struct Npc{
	Hp hp{5};
};

struct DefaultWeapon {
	std::string name; // string used as name
	Damage dmg{};
};

struct CustomWeapon { // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
	Name name;
	std::vector<DefaultWeapon> others{
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
		auto hp_opt = get(*suspect, Parameter::Hp);

		if (hp_opt) {
			Hp& hp = Get<Hp>(hp_opt.value());
			if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) { // when got Damagingable property
				hp.value() -= obj.dmg.value();
			}

			for (auto& other : obj.others) {
				operator()(other, hp);
			}
		}
		return true;
	}

	bool operator()(Damagingable auto& obj, Hp& hp_ref) const { // sub attacks
		hp_ref.value() -= obj.dmg.value();

		std::cout << "\t\t for " << obj.dmg.value() << " dmg";
		std::cout << " with " << static_cast<std::string>(obj.name) << '\n';
		return true;
	}
};
