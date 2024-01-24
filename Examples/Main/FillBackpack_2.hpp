#pragma once

void fillBackpack2(auto& backpack) {
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
    auto gustav_2 = add_properties<Weapon, Living, Healing, Living, Healing>(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ Damage{32},  // ? move damage here (it's it correct place)
        /*cureHealth*/ CureHealth{30});
    add_properties<NoNameWeapon, Living, Healing, Living, Healing, Naming>(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ Damage{32},  // ? move damage here (it's it correct place)
        /*cureHealth*/ CureHealth{30});
    static_assert(std::is_same_v<decltype(gustav_2), add_properties<Weapon, Living, Healing>>);
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
        CureHealth{20}));
    backpack.emplace_back(Healing<Potion>{
        Name{"SMALL_HEALING_POTION"},
        CureHealth{10}});  // TODO: add removing effects
    backpack.emplace_back(Protecting<Potion>(
        Name{"SHIELD_POTION"},
        ArmorClass{
            4,
            BodyLocation::Internal,
            {EffectType::Shock}}));  // TODO: ths protection should be temporary
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
        CureHealth{15}));
}
