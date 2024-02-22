#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessDamage.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_damage = Damage{10};
constexpr auto default_damage_change = Damage{100};

TEST(custom_access_test, AccessDamage) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        default_damage};

    decltype(auto) damage = type.getDamage();
    decltype(auto) damage_const = std::as_const(type).getDamage();

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = type.getDamage();

    EXPECT_EQ(damage, default_damage_change);
}

TEST(custom_access_test, CustomAccessDamage) {
    MockCustomAccessDamage mock;
    traits::CustomAccessDamage<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_damage;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) damage = traits::accessDamage::get(type);
    decltype(auto) damage_const = traits::accessDamage::get(std::as_const(type));

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = traits::accessDamage::get(type);

    EXPECT_EQ(damage, default_damage_change);
}
