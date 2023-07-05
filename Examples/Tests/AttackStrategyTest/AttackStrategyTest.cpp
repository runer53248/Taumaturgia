#include <gtest/gtest.h>
#include "Examples/Structs/CustomWeapon.hpp"
#include "Examples/Structs/Player.hpp"
#include "Examples/Structs/Weapon.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

#include "Examples/preety_print.hpp"

constexpr auto max_health = 100;

constexpr auto damage_1 = 10;
constexpr auto damage_2 = 20;
constexpr auto damage_3 = 32;

constexpr auto effect_1 = Effect{EffectType::Stun};
constexpr auto effect_2 = Effect{EffectType::Freeze, Duration{1, DurationType::Round}};

TEST(AttackStrategyTest, Weapon_attack_effect) {
    Object weapon{
        Weapon{
            Name{"SWORD"},
            Damage{damage_1, effect_1}}};
    Object player{
        Living<Player>{
            Name{"Player"},
            Health{max_health}}};

    auto hp = getOpt<Parameter::Health>(player);
    EXPECT_EQ(hp.value().get().value(), max_health);
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";

    ActionStatus status = weapon.attack(&weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player);
    auto expected_current_hp = max_health - damage_1;
    EXPECT_EQ(hp.value().get().value(), expected_current_hp);
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";
}

TEST(AttackStrategyTest, CustomWeapon_subattack_effects) {
    std::vector<DefaultWeapon> subAttacks{
        DefaultWeapon{
            Name{"Light weapon"},
            Damage{damage_1, effect_2}},
        DefaultWeapon{
            Name{"Medium weapon"},
            Damage{damage_2}}};

    Object weapon{CustomWeapon{
        Name{"Custom"},
        subAttacks}};

    Object weapon_2{
        Damaging<CustomWeapon>{
            Name{"New_Custom_SWORD"},
            Damage{damage_3, effect_1},
            subAttacks}};

    Object player{
        Living<Player>{
            Name{"Player"},
            Health{max_health}}};

    auto hp = getOpt<Parameter::Health>(player);
    EXPECT_EQ(hp.value().get().value(), max_health);
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";

    ActionStatus status = weapon.attack(&weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player);
    auto expected_current_hp = max_health - damage_1 - damage_2;
    EXPECT_EQ(hp.value().get().value(), expected_current_hp);
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";

    print_object(weapon_2);
    status = weapon_2.attack(&weapon_2, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player);
    expected_current_hp = expected_current_hp - damage_1 - damage_2 - damage_3;
    EXPECT_EQ(hp.value().get().value(), expected_current_hp);
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";
}
