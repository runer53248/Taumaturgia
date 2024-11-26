#pragma once
#include "Usage/Properties.hpp"

struct Living_type {
    Name name;
    Health hp;
};

#include "Examples/structs.hpp"
#include "Examples/Structs/EmptyType.hpp"

using ArmorSet = add_properties_ordered<Type, Naming, Wearing>;

using living_weapon = add_properties_ordered<Weapon, Living>;
using living_player = add_properties_ordered<Player, Living>;
using living_enemy = add_properties_ordered<Enemy, Living>;

using named_npc = add_properties_ordered<Npc, Naming>;

using restoring_potion = add_properties_ordered<Potion, Restoring>;

using weapon_1 = add_properties_ordered<Weapon, Damaging>;
using weapon_2 = Weapon;
using weapon_3 = CustomWeapon;
using weapon_4 = add_properties_ordered<CustomWeapon, Damaging>;   // CustomWeapon became Damagingable
using weapon_5 = add_properties_ordered<DefaultWeapon, Damaging>;
using weapon_6 = add_properties_ordered<Weapon, Living, Healing, Living, Healing>;
using weapon_7 = add_properties_ordered<NoNameWeapon, Living, Healing, Living, Healing, Naming>;

static_assert(std::is_same_v<weapon_6, add_properties_ordered<Weapon, Living, Healing>>);

using armor_1 = Armor;
using armor_2 = add_properties_ordered<Armor, Protecting>;
using armor_3 = add_properties_ordered<Helmet, Damaging>;
using armor_4 = Helmet;

using potion_1 = add_properties_ordered<Potion, Healing>;
using potion_2 = add_properties_ordered<Potion, Protecting>;

using scroll_1 = Scroll;
using scroll_2 = add_properties_ordered<Scroll, Restoring>;
using scroll_3 = add_properties_ordered<Scroll, Damaging>;
using scroll_4 = add_properties_ordered<Scroll, Damaging, Healing>;

using player_type = add_properties_ordered<Player, Living>;
