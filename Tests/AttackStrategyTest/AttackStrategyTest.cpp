#include <gtest/gtest.h>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/Structs/CustomWeapon.hpp"
#include "Examples/Structs/Player.hpp"
#include "Examples/Structs/Weapon.hpp"
#include "Usage/DefaultStrategies.hpp"

constinit const auto max_health = 100;

constinit const auto damage_1 = 10;
constinit const auto damage_2 = 20;
constinit const auto damage_3 = 32;

constinit const auto effect_1 = Effect{EffectType::Stun};
constinit const auto effect_2 = Effect{EffectType::Freeze, Duration{1, DurationType::Round}};

TEST(AttackStrategyTest, initial_player_state) {
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    Health& hp = getOpt<Properties::Health>(player).value();
    EXPECT_EQ(hp.value(), max_health);
    EXPECT_FALSE(hp.effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}

TEST(AttackStrategyTest, Weapon_attack_effect) {
    Object weapon{Weapon{Name{"SWORD"}, Damage{damage_1, effect_1}}};
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    Health& hp = getOpt<Properties::Health>(player).value();
    EXPECT_EQ(hp.value(), max_health);
    EXPECT_FALSE(hp.effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";

    ActionStatus status = attack(weapon, &weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Properties::Health>(player).value();
    auto expected_current_hp = max_health - damage_1;
    EXPECT_EQ(hp.value(), expected_current_hp);
    EXPECT_TRUE(hp.effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}

TEST(AttackStrategyTest, CustomWeapon_subattack_effects) {
    std::vector<DefaultWeapon> subAttacks{
        DefaultWeapon{Name{"Light weapon"}, Damage{damage_1, effect_2}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{damage_2}}};

    Object weapon_1{CustomWeapon{Name{"Custom"}, subAttacks}};
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    print_object(weapon_1);
    ActionStatus status = attack(weapon_1, &weapon_1, &player);
    std::cout << status << "\n\n";
    Health& hp = getOpt<Properties::Health>(player).value();
    auto expected_current_hp = max_health - damage_1 - damage_2;

    EXPECT_EQ(hp.value(), expected_current_hp);
    EXPECT_FALSE(hp.effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}

TEST(AttackStrategyTest, Damaging_CustomWeapon_subattack_effects) {
    std::vector<DefaultWeapon> subAttacks{
        DefaultWeapon{Name{"Light weapon"}, Damage{damage_1, effect_2}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{damage_2}}};

    Object weapon_2{Damaging<CustomWeapon>{Name{"New_Custom_SWORD"}, Damage{damage_3, effect_1}, subAttacks}};
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    print_object(weapon_2);
    auto status = attack(weapon_2, &weapon_2, &player);
    std::cout << status << "\n\n";
    Health& hp = getOpt<Properties::Health>(player).value();
    auto expected_current_hp = max_health - damage_1 - damage_2 - damage_3;

    EXPECT_EQ(hp.value(), expected_current_hp);
    EXPECT_TRUE(hp.effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}
