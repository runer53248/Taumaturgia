#pragma once
#include "Usage/Properties.hpp"

struct Living_type {
    Name name;
    Health hp;
};

#include "Examples/structs.hpp"
#include "Examples/Structs/EmptyType.hpp"

using ArmorSet = add_properties<Type, Naming, Wearing>;

using living_weapon = add_properties<Weapon, Living>;
using living_player = add_properties<Player, Living>;
using living_enemy = add_properties<Enemy, Living>;

using named_npc = add_properties<Npc, Naming>;

using restoring_potion = add_properties<Potion, Restoring>;

using weapon_1 = add_properties<Weapon, Damaging>;
using weapon_2 = Weapon;
using weapon_3 = CustomWeapon;
using weapon_4 = add_properties<CustomWeapon, Damaging>;   // CustomWeapon became Damagingable
using weapon_5 = add_properties<DefaultWeapon, Damaging>;
using weapon_6 = add_properties<Weapon, Living, Healing, Living, Healing>;
using weapon_7 = add_properties<NoNameWeapon, Living, Healing, Living, Healing, Naming>;
static_assert(std::is_same_v<weapon_6, add_properties<Weapon, Living, Healing>>);

using armor_1 = Armor;
using armor_2 = add_properties<Armor, Protecting>;
using armor_3 = add_properties<Helmet, Damaging>;
using armor_4 = Helmet;

using potion_1 = add_properties<Potion, Healing>;
using potion_2 = add_properties<Potion, Protecting>;

using scroll_1 = Scroll;
using scroll_2 = add_properties<Scroll, Restoring>;
using scroll_3 = add_properties<Scroll, Damaging>;
using scroll_4 = add_properties<Scroll, Damaging, Healing>;

using player_type = add_properties<Player, Living>;
