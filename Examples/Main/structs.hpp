#pragma once

#ifdef WITH_ADD_PROPERTIES
    // use add_properties for creating type with properties
    #include "Examples/Structs/CustomWeapon.hpp"

    struct Type {};

    using NoNameWeapon = add_properties<Type, Damaging>;
    using Weapon = add_properties<Type, Naming, Damaging>;
    using Player = add_properties<Type, Naming, Wearing, Restoring>;
    using Enemy = add_properties<Type, Naming>;
    using Scroll = add_properties<Type, Naming>;
    using Potion = add_properties<Type, Naming>;
    using Armor = add_properties<Type, Naming, Protecting>;
    using Helmet = add_properties<Type, Naming, Protecting>;
    using Npc = add_properties<Type, Living>;

    using living_weapon = add_properties<Weapon, Living>;
    using living_player = add_properties<Player, Living>;
    using living_enemy = add_properties<Enemy, Living>;

    using named_npc = add_properties<Npc, Naming>;

    using restoring_potion = add_properties<Potion, Restoring>;

    using weapon_1 = add_properties<Weapon, Damaging>;
    using weapon_2 = Weapon;
    using weapon_3 = CustomWeapon;
    using weapon_4 = add_properties<CustomWeapon, Damaging>;
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
#else
    // use old method of creating type with properties
    #include "Examples/structs.hpp"

    using living_weapon = Living<Weapon>;
    using living_player = Living<Player>;
    using living_enemy = Living<Enemy>;

    using named_npc = Naming<Npc>;

    using restoring_potion = Restoring<Potion>;

    using weapon_1 = Damaging<Weapon>;
    using weapon_2 = Weapon;
    using weapon_3 = CustomWeapon;
    using weapon_4 = Damaging<CustomWeapon>;
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
#endif
