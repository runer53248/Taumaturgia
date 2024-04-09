#include <gtest/gtest.h>
#include "Taumaturgia/Properties/Properties.hpp"

struct Type {
    Name name;
};

using restoring_protecting_damaging_type = Restoring<Protecting<Damaging<Type>>>;

Name default_name{"Default"};
const Name const_default_name{"Default"};

constinit const auto damage_value{10};
constinit const Effect damage_effect{EffectType::Bleed};
constinit const Damage default_damage{damage_value, damage_effect};
constinit const Damage const_default_damage{damage_value, damage_effect};

constinit const auto armor_value{4};
constinit const auto armor_location{BodyLocation::Internal};
constinit const auto protecting_effect_initializer = {EffectType::Sleep};
Protection default_protection{ArmorClass{armor_value, armor_location, protecting_effect_initializer}};
const Protection const_default_protection{ArmorClass{armor_value, armor_location, protecting_effect_initializer}};

constinit const auto restore_effect_initializer = {EffectType::Sleep, EffectType::Sleep};
EffectTypeContainer default_restore{restore_effect_initializer};
const EffectTypeContainer const_default_restore{restore_effect_initializer};

#ifndef NO_PREMADE_PROPERTIES

// empty c-tor
TEST(CtorTest, empty) {
    restoring_protecting_damaging_type type{};

    EXPECT_EQ(type.name, Name{});
    EXPECT_EQ(type.getRestoreEffects(), EffectTypeContainer{});
    EXPECT_EQ(type.getProtection(), Protection{});
    EXPECT_EQ(type.getDamage(), Damage{});
}

// empty c-tor
TEST(CtorTest, name) {
    restoring_protecting_damaging_type type{
        default_name};

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), EffectTypeContainer{});
    EXPECT_EQ(type.getProtection(), Protection{});
    EXPECT_EQ(type.getDamage(), Damage{});
}

TEST(CtorTest, all_arguments) {
    restoring_protecting_damaging_type type{
        default_name,
        default_restore,
        default_protection,
        default_damage};

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), default_restore);
    EXPECT_EQ(type.getProtection(), default_protection);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, all_const_arguments) {
    restoring_protecting_damaging_type type{
        const_default_name,
        const_default_restore,
        const_default_protection,
        const_default_damage};

    EXPECT_EQ(type.name, const_default_name);
    EXPECT_EQ(type.getRestoreEffects(), const_default_restore);
    EXPECT_EQ(type.getProtection(), const_default_protection);
    EXPECT_EQ(type.getDamage(), const_default_damage);
}

TEST(CtorTest, arguments_are_initializer_list) {
    restoring_protecting_damaging_type type{
        default_name,
        restore_effect_initializer,                                              // restoring
        ArmorClass{armor_value, armor_location, protecting_effect_initializer},  // protecting
        Damage{damage_value, damage_effect}};                                    // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), default_restore);
    EXPECT_EQ(type.getProtection(), default_protection);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, arguments_are_tuples_rvalues) {
    restoring_protecting_damaging_type type{
        default_name,
        std::tuple(restore_effect_initializer),                                  // restoring
        std::tuple(armor_value, armor_location, protecting_effect_initializer),  // protecting
        std::tuple(damage_value, damage_effect)};                                // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), default_restore);
    EXPECT_EQ(type.getProtection(), default_protection);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, arguments_are_tuples_lvalues) {
    std::tuple restoring_tuple{restore_effect_initializer};
    std::tuple protecting_tuple{armor_value, armor_location, protecting_effect_initializer};
    std::tuple damaging_tuple{damage_value, damage_effect};

    restoring_protecting_damaging_type type{
        default_name,
        restoring_tuple,   // restoring
        protecting_tuple,  // protecting
        damaging_tuple};   // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), default_restore);
    EXPECT_EQ(type.getProtection(), default_protection);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, last_arguments_is_lvalues) {
    restoring_protecting_damaging_type type{
        default_name,
        std::ignore,      // restoring
        std::ignore,      // protecting
        default_damage};  // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, last_arguments_is_rvalue) {
    restoring_protecting_damaging_type type{
        default_name,
        std::ignore,                           // restoring
        std::ignore,                           // protecting
        Damage{damage_value, damage_effect}};  // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, last_arguments_is_tuple_lvalue) {
    std::tuple damaging_tuple{damage_value, damage_effect};

    restoring_protecting_damaging_type type{
        default_name,
        std::ignore,      // restoring
        std::ignore,      // protecting
        damaging_tuple};  // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, last_arguments_is_tuple_rvalue) {
    restoring_protecting_damaging_type type{
        default_name,
        std::ignore,                               // restoring
        std::ignore,                               // protecting
        std::tuple{damage_value, damage_effect}};  // damaging

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, first_argument) {
    restoring_protecting_damaging_type type{
        default_name,
        default_restore};

    EXPECT_EQ(type.name, default_name);
    EXPECT_EQ(type.getRestoreEffects(), default_restore);
}

TEST(CtorTest, incorrect_argument_tuple_rvalue) {
    try {
        restoring_protecting_damaging_type type{
            default_name,
            std::tuple{"test"},
            std::ignore,
            std::tuple{"test"}};
        FAIL();
    } catch (const std::logic_error& err) {
        EXPECT_STREQ("Can't create EffectTypeContainer from given tuple.", err.what());
    }
}

TEST(CtorTest, incorrect_argument_tuple_lvalue) {
    try {
        std::tuple tuple_invalid_for_restoring{"test"};
        std::tuple tuple_invalid_for_damaging{"test"};

        restoring_protecting_damaging_type type{
            default_name,
            tuple_invalid_for_restoring,
            std::ignore,
            tuple_invalid_for_damaging};
        FAIL();
    } catch (const std::logic_error& err) {
        EXPECT_STREQ("Can't create EffectTypeContainer from given tuple.", err.what());
    }
}

TEST(CtorTest, incorrect_argument_tuple_lvalue_move) {
    try {
        std::tuple tuple_invalid_for_restoring{"test"};
        std::tuple tuple_invalid_for_damaging{"test"};

        restoring_protecting_damaging_type type{
            default_name,
            std::move(tuple_invalid_for_restoring),
            std::ignore,
            std::move(tuple_invalid_for_damaging)};
        FAIL();
    } catch (const std::logic_error& err) {
        EXPECT_STREQ("Can't create EffectTypeContainer from given tuple.", err.what());
    }
}

using container = std::variant<std::monostate, Damage, Protection, EffectTypeContainer>;

TEST(CtorTest, arguments_variant_rvalue) {
    restoring_protecting_damaging_type type{
        default_name,
        container{default_restore},     // restoring
        container{default_protection},  // protecting
        container{default_damage}};     // damaging

    EXPECT_EQ(type.getRestoreEffects(), default_restore);
    EXPECT_EQ(type.getProtection(), default_protection);
    EXPECT_EQ(type.getDamage(), default_damage);
}

TEST(CtorTest, arguments_wrong_variant_rvalue) {
    try {
        restoring_protecting_damaging_type type{
            default_name,
            container{default_damage},   // restoring
            container{default_damage},   // protecting
            container{default_damage}};  // damaging

        EXPECT_EQ(type.getRestoreEffects(), EffectTypeContainer{});
        EXPECT_EQ(type.getProtection(), Protection{});
        EXPECT_EQ(type.getDamage(), default_damage);

        // FAIL();
    } catch (const std::exception& err) {
        // EXPECT_STREQ("std::get: wrong index for variant", err.what());
        FAIL();
    }
}

TEST(CtorTest, arguments_wrong_variant_lvalue) {
    try {
        auto damage_variant = container{default_damage};

        restoring_protecting_damaging_type type{
            default_name,
            damage_variant,   // restoring
            damage_variant,   // protecting
            damage_variant};  // damaging

        EXPECT_EQ(type.getRestoreEffects(), EffectTypeContainer{});
        EXPECT_EQ(type.getProtection(), Protection{});
        EXPECT_EQ(type.getDamage(), default_damage);

        // FAIL();
    } catch (const std::exception& err) {
        // EXPECT_STREQ("std::get: wrong index for variant", err.what());
        FAIL();
    }
}

using limited_container = std::variant<std::monostate, Damage>;

TEST(CtorTest, arguments_wrong_limited_variant_rvalue) {
    try {
        restoring_protecting_damaging_type type{
            default_name,
            limited_container{default_damage},   // restoring
            limited_container{default_damage},   // protecting
            limited_container{default_damage}};  // damaging

        EXPECT_EQ(type.getRestoreEffects(), EffectTypeContainer{});
        EXPECT_EQ(type.getProtection(), Protection{});
        EXPECT_EQ(type.getDamage(), default_damage);

        // FAIL();
    } catch (const std::exception& err) {
        // EXPECT_STREQ("std::get: wrong index for variant", err.what());
        FAIL();
    }
}

#endif
