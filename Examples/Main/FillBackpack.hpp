#pragma once

void fillBackpack(auto& backpack) {
    backpack.emplace_back(Damaging<Weapon>{
        Name{"SWORD"},
        Damage{16}});
    backpack.emplace_back(Weapon{
        Name{"GIANT_SWORD"},
        Damage{
            32,
            DamageType::Physical}});
    backpack.emplace_back(CustomWeapon{
        Name{"Custom_SWORD"}});
    backpack.emplace_back(Damaging<CustomWeapon>{
        Name{"New_Custom_SWORD"},
        Damage{32}});  // became Damagingable - custom AttackStrategy_<CustomWeapon> from 'CustomWeapon.hpp' will handle it
    backpack.emplace_back(Damaging<DefaultWeapon>{
        Name{"Default_BATTLE_SWORD"},
        Damage{32}});

    // arguments in constructor are from left to right - same as added properties (only Naming requires to be most right as all properties need to be used on Namingable type)
    auto gustav_2 = Living<Healing<Living<Healing<Weapon>>>>(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ Health{30},
        Damage{32});
    Living<Healing<Living<Healing<Naming<NoNameWeapon>>>>>(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ Health{30},
        Damage{32});
    static_assert(std::is_same_v<decltype(gustav_2), Living<Healing<Weapon>>>);
    backpack.emplace_back(gustav_2);

    backpack.emplace_back(Armor{
        Name{"CHAIN_MAIL"},
        Protection{
            8,
            BodyLocation::Body}});
    backpack.emplace_back(Protecting<Armor>{
        Name{"HALF_PLATE"},
        Protection{
            ArmorClass{12}}});

    backpack.emplace_back(Damaging<Helmet>{
        Name{"BATTLE_HELM"},
        Damage{10},
        ArmorClass{
            4,
            BodyLocation::Head,
            {EffectType::Daze}}});
    backpack.emplace_back(Helmet{
        Name{"VIKING_HELM"},
        ArmorClass{
            2,
            BodyLocation::Head,
            {EffectType::Stun}}});
    backpack.emplace_back(Healing<Potion>(
        Name{"HEALING_POTION"},
        Health{20}));
    backpack.emplace_back(Healing<Potion>{
        Name{"SMALL_HEALING_POTION"},
        Health{10}});  // TODO: add removing effects
    backpack.emplace_back(Protecting<Potion>(
        Name{"SHIELD_POTION"},
        ArmorClass{
            4,
            BodyLocation::Internal,
            {EffectType::Sleep}}));
    backpack.emplace_back(Scroll{
        Name{"USELESS_SCROLL"}});
    backpack.emplace_back(Scroll{
        Name{"EMPTY_SCROLL"}});
    backpack.emplace_back(Restoring<Scroll>{
        Name{"AWAKE_SCROLL"},
        {EffectType::Sleep}});
    backpack.emplace_back(Damaging<Scroll>(
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}}));
    backpack.emplace_back(Damaging<Healing<Scroll>>(
        Name{"VAMPIRIC_TOUCH_SCROLL"},
        Damage{
            30,
            DamageType::Divine,
            Effect{EffectType::Devour}},
        Health{15}));
}
