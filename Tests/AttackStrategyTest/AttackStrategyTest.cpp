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

            for (auto& other : obj.others) {
                status = default_attack_behavior(other, suspect);
                print_subAttacks(other);
            }
            return status;
        }

        bool print_subAttacks(Damagingable auto& obj) const {
            std::cout << "\t\t " << obj << "\n";
            return true;
        }
    };

#else
    #include "Examples/Structs/CustomWeapon.hpp"
    #include "Examples/Structs/Player.hpp"
    #include "Examples/Structs/Weapon.hpp"
    #include "Object/DefaultStrategies.hpp"
    #include "Object/Properties/Properties.hpp"
#endif

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
    ASSERT_TRUE(hp.has_value());

    EXPECT_EQ(hp.value().get().value(), max_health);
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";

    ActionStatus status = weapon.attack(&weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player);
    ASSERT_TRUE(hp.has_value());

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
    ASSERT_TRUE(hp.has_value());

    EXPECT_EQ(hp.value().get().value(), max_health);
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_FALSE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";

    ActionStatus status = weapon.attack(&weapon, &player);
    std::cout << status << "\n\n";

    hp = getOpt<Parameter::Health>(player);
    ASSERT_TRUE(hp.has_value());

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
    ASSERT_TRUE(hp.has_value());

    expected_current_hp = expected_current_hp - damage_1 - damage_2 - damage_3;
    EXPECT_EQ(hp.value().get().value(), expected_current_hp);
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_1));
    EXPECT_TRUE(hp.value().get().effects().isEffectType(effect_2));
    hp.and_then(print_hp);
    std::cout << "\n\n";
}
