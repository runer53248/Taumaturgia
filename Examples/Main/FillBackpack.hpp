#pragma once

void fillBackpack(auto& backpack) {
#ifdef WITH_ADD_PROPERTIES
    using weapon_1 = add_properties<Weapon, Damaging>;
    using weapon_2 = Weapon;
    using weapon_3 = CustomWeapon;
    using weapon_4 = add_properties<CustomWeapon, Damaging>;
    using weapon_5 = add_properties<DefaultWeapon, Damaging>;
#else
    using weapon_1 = Damaging<Weapon>;
    using weapon_2 = Weapon;
    using weapon_3 = CustomWeapon;
    using weapon_4 = Damaging<CustomWeapon>;
    using weapon_5 = Damaging<DefaultWeapon>;
#endif

    backpack.emplace_back(weapon_1{
        Name{"SWORD"},
        Damage{16}});

    backpack.emplace_back(weapon_2{
        Name{"GIANT_SWORD"},
        Damage{32,
               DamageType::Physical}});

    backpack.emplace_back(weapon_3{
        Name{"Custom_SWORD"}});

    backpack.emplace_back(weapon_4{
        Name{"New_Custom_SWORD"},
        Damage{32}});  // became Damagingable - custom AttackStrategy_<CustomWeapon> from 'CustomWeapon.hpp' will handle it

    backpack.emplace_back(weapon_5{
        Name{"Default_BATTLE_SWORD"},
        Damage{32}});

#ifdef WITH_ADD_PROPERTIES
    using weapon_6 = add_properties<Weapon, Living, Healing, Living, Healing>;
    using weapon_7 = add_properties<NoNameWeapon, Living, Healing, Living, Healing, Naming>;

    static_assert(std::is_same_v<weapon_6, add_properties<Weapon, Living, Healing>>);

    auto gustav_2 = weapon_6(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ Damage{32},  // ? move damage here (it's it correct place)
        /*cureHealth*/ CureHealth{30});
    backpack.emplace_back(gustav_2);

    weapon_7(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ Damage{32},  // ? move damage here (it's it correct place)
        /*cureHealth*/ CureHealth{30});
#else
    using weapon_6 = Living<Healing<Living<Healing<Weapon>>>>;
    using weapon_7 = Living<Healing<Living<Healing<Naming<NoNameWeapon>>>>>;

    static_assert(std::is_same_v<weapon_6, Living<Healing<Weapon>>>);

    auto gustav_2 = weapon_6(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ CureHealth{30},
        Damage{32});
    weapon_7(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ CureHealth{30},
        Damage{32});
    static_assert(std::is_same_v<decltype(gustav_2), Living<Healing<Weapon>>>);
    backpack.emplace_back(gustav_2);
#endif

#ifdef WITH_ADD_PROPERTIES
    using armor_1 = Armor;
    using armor_2 = add_properties<Armor, Protecting>;
    using armor_3 = add_properties<Helmet, Damaging>;
    using armor_4 = Helmet;
#else
    using armor_1 = Armor;
    using armor_2 = Protecting<Armor>;
    using armor_3 = Damaging<Helmet>;
    using armor_4 = Helmet;
#endif

    backpack.emplace_back(armor_1{
        Name{"CHAIN_MAIL"},
        Protection{
            8,
            BodyLocation::Body}});

    backpack.emplace_back(armor_2{
        Name{"HALF_PLATE"},
        Protection{
            ArmorClass{12}}});

    backpack.emplace_back(armor_3{
        Name{"BATTLE_HELM"},
        Damage{10},
        ArmorClass{
            4,
            BodyLocation::Head,
            {EffectType::Daze}}});

    backpack.emplace_back(armor_4{
        Name{"VIKING_HELM"},
        ArmorClass{
            2,
            BodyLocation::Head,
            {EffectType::Stun}}});

#ifdef WITH_ADD_PROPERTIES
    using potion_1 = add_properties<Potion, Healing>;
    using potion_2 = add_properties<Potion, Protecting>;
#else
    using potion_1 = Healing<Potion>;
    using potion_2 = Protecting<Potion>;
#endif

    backpack.emplace_back(potion_1(
        Name{"HEALING_POTION"},
        CureHealth{20}));

    backpack.emplace_back(potion_1{
        Name{"SMALL_HEALING_POTION"},
        CureHealth{10}});  // TODO: add removing effects

    backpack.emplace_back(potion_2(
        Name{"SHIELD_POTION"},
        ArmorClass{
            4,
            BodyLocation::Internal,
            {EffectType::Shock}}));  // TODO: ths protection should be temporary

#ifdef WITH_ADD_PROPERTIES
    using scroll_1 = Scroll;
    using scroll_2 = add_properties<Scroll, Restoring>;
    using scroll_3 = add_properties<Scroll, Damaging>;
    using scroll_4 = add_properties<Scroll, Damaging, Healing>;
#else
    using scroll_1 = Scroll;
    using scroll_2 = Restoring<Scroll>;
    using scroll_3 = Damaging<Scroll>;
    using scroll_4 = Damaging<Healing<Scroll>>;
#endif

    backpack.emplace_back(scroll_1{
        Name{"USELESS_SCROLL"}});

    backpack.emplace_back(scroll_1{
        Name{"EMPTY_SCROLL"}});

    backpack.emplace_back(scroll_2{
        Name{"AWAKE_SCROLL"},
        {EffectType::Sleep}});

    backpack.emplace_back(scroll_3(
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}}));

    backpack.emplace_back(scroll_4(
        Name{"VAMPIRIC_TOUCH_SCROLL"},
        Damage{
            30,
            DamageType::Divine,
            Effect{EffectType::Devour}},
        CureHealth{15}));
}
