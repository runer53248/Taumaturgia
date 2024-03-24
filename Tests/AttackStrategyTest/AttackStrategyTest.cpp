#include <gtest/gtest.h>
#include "Examples/PreetyPrint/preety_print.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

struct Type {};

using Weapon = add_properties<Type, Naming, Damaging>;
using DefaultWeapon = add_properties<Type, Naming, Damaging>;
using Player = add_properties<Type, Naming, Restoring, Wearing>;

struct CustomType {
    std::vector<DefaultWeapon> others{
        DefaultWeapon{Name{"Light weapon"}, Damage{10}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{20}}};
};

using CustomWeapon = add_properties<CustomType, Naming>;

template <>
struct AttackStrategy_<CustomWeapon> {
    ActionStatus operator()(auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        ActionStatus status{ActionStatus::None};

        if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) {
            status = default_attack_behavior(obj, suspect);
        }

        if constexpr (Damagingable<typename decltype(obj.others)::value_type>) {
            for (auto& other : obj.others) {
                status = default_attack_behavior(other, suspect);
                std::cout << "\t\t " << other << "\n";
            }
        }
        return status;
    }
};

#else
#include "Examples/Structs/CustomWeapon.hpp"
#include "Examples/Structs/Player.hpp"
#include "Examples/Structs/Weapon.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"
#endif

constinit auto max_health = 100;

constinit auto damage_1 = 10;
constinit auto damage_2 = 20;
constinit auto damage_3 = 32;

constinit auto effect_1 = Effect{EffectType::Stun};
constinit auto effect_2 = Effect{EffectType::Freeze, Duration{1, DurationType::Round}};

TEST(AttackStrategyTest, initial_player_state) {
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    Health& hp = getOpt<Parameter::Health>(player).value();
    EXPECT_EQ(hp.value(), max_health);
    EXPECT_FALSE(hp.effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}

TEST(AttackStrategyTest, Weapon_attack_effect) {
    Object weapon{Weapon{Name{"SWORD"}, Damage{damage_1, effect_1}}};
    Object player{Living<Player>{Name{"Player"}, Health{max_health}}};

    Health& hp = getOpt<Parameter::Health>(player).value();
    EXPECT_EQ(hp.value(), max_health);
    EXPECT_FALSE(hp.effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";

    ActionStatus status = weapon.attack(&weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player).value();
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
    ActionStatus status = weapon_1.attack(&weapon_1, &player);
    std::cout << status << "\n\n";
    Health& hp = getOpt<Parameter::Health>(player).value();
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
    auto status = weapon_2.attack(&weapon_2, &player);
    std::cout << status << "\n\n";
    Health& hp = getOpt<Parameter::Health>(player).value();
    auto expected_current_hp = max_health - damage_1 - damage_2 - damage_3;

    EXPECT_EQ(hp.value(), expected_current_hp);
    EXPECT_TRUE(hp.effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.effects().isEffectType(effect_2));
    print_hp(std::ref(hp));
    std::cout << "\n\n";
}
