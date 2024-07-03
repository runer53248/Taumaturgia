#pragma once
#include "Usage/Properties.hpp"

struct Living_type {
    Name name;
    Health hp;
};

#include "Examples/structs.hpp"
#include "Examples/Structs/EmptyType.hpp"

using ArmorSet = Wearing<Naming<Type>>;

using living_weapon = Living<Weapon>;
using living_player = Living<Player>;
using living_enemy = Living<Enemy>;

using named_npc = Naming<Npc>;

using restoring_potion = Restoring<Potion>;

using weapon_1 = Damaging<Weapon>;
using weapon_2 = Weapon;
using weapon_3 = CustomWeapon;
using weapon_4 = Damaging<CustomWeapon>;   // CustomWeapon became Damagingable
using weapon_5 = Damaging<DefaultWeapon>;
using weapon_6 = Living<Healing<Living<Healing<Weapon>>>>;
using weapon_7 = Living<Healing<Living<Healing<Naming<NoNameWeapon>>>>>;
static_assert(std::is_same_v<weapon_6, Living<Healing<Weapon>>>);

using armor_1 = Armor;
using armor_2 = Protecting<Armor>;
using armor_3 = Damaging<Helmet>;
using armor_4 = Helmet;

using potion_1 = Healing<Potion>;
using potion_2 = Protecting<Potion>;

using scroll_1 = Scroll;
using scroll_2 = Restoring<Scroll>;
using scroll_3 = Damaging<Scroll>;
using scroll_4 = Damaging<Healing<Scroll>>;

using player_type = Living<Player>;
