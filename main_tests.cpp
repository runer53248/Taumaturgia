#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include <vector>

struct Scroll {
	Name name;
};

struct Weapon {
	Name name;
	Damage dmg{};
};

struct Player{
	std::string name;
};

struct Enemy{
	Name name;
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
	static_assert(std::is_same_v< GetStrategy<Default>, GetStrategy<Npc> >); // Npc will use default Get strategy - Livable concept pass
	static_assert(std::is_same_v< GetStrategy<Default>, GetStrategy<Living<Player>> >); // Player will use default Get strategy - Livable concept pass

	static_assert(std::is_same_v< Living_<Player>, Living<Player> >); // Livable traits added
	static_assert(std::is_same_v< Npc, Living<Npc> >); // Livable concept pass

	static_assert(not std::is_same_v< AttackStrategy<Default>, AttackStrategy<Player> >);

	static_assert(std::is_same_v< GetStrategy<Default>, GetStrategy<Damaging<Living<Healing<Player>>>> >);
	static_assert(std::is_same_v< Damaging<Living<Healing<Living<Player>>>>, Damaging<Damaging<Living<Living<Healing<Living<Player>>>>>> >);
	static_assert(std::is_same_v< Damaging<Npc>, Damaging<Living<Npc>> >);

	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<Healing<Weapon>> >);
	static_assert(std::is_same_v< HealStrategy<Default>, HealStrategy<Healing<Weapon>> >);
	static_assert(not std::is_same_v< HealStrategy<Default>, HealStrategy<Weapon> >);
	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<DefaultWeapon> >);
	static_assert(std::is_same_v< AttackStrategy<Weapon>, AttackStrategy<Healing<DefaultWeapon>> >);

	static_assert(std::is_same_v< DefaultWeapon, Damaging<Damaging<DefaultWeapon>> >);
	static_assert(not std::is_same_v< Enemy, Damaging<Enemy> >);
	static_assert(std::is_same_v< Damaging<Enemy>, Damaging<Damaging<Enemy>> >);
	
	auto sword = Damaging<Weapon>{ Name{"SWORD"}, Damage{16}};
	auto giant_sword = Weapon{ Name{"GIANT_SWORD"}, Damage{32}};
	static_assert(sizeof(sword) == sizeof(giant_sword));

	static_assert(sizeof(Damaging<Scroll>) == sizeof(Damaging<Damaging<Scroll>>));
	static_assert(sizeof(Weapon) == sizeof(Damaging<Damaging<Weapon>>));

	return 0;
}
