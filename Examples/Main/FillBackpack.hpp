#pragma once
#ifdef WITH_ADD_PROPERTIES
#include "structs_aP.hpp"
#else
#include "structs_no_aP.hpp"
#endif

void fillBackpack(auto& backpack) {
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
        Damage{32}});

    backpack.emplace_back(weapon_5{
        Name{"Default_BATTLE_SWORD"},
        Damage{32}});

#ifdef WITH_ADD_PROPERTIES
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
    auto gustav_2 = weapon_6(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ CureHealth{30},
        /*dmg*/ Damage{32});
    backpack.emplace_back(gustav_2);

    weapon_7(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ CureHealth{30},
        /*dmg*/ Damage{32});
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
            {EffectType::Shock}}));  // TODO: this protection should be temporary

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
