#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessArmorWear.hpp"

constexpr auto default_name = "TestName";
const auto default_armor = ProtectionContainer{10};
const auto default_armor_change = ProtectionContainer{100};

TEST(custom_access_test, AccessArmorWear) {
    TestType type{
        Name{default_name},
        std::ignore,
        default_armor};

    decltype(auto) armor = type.getArmorWear();
    decltype(auto) armor_const = std::as_const(type).getArmorWear();

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;
    armor = type.getArmorWear();

    EXPECT_EQ(armor, default_armor_change);
}

TEST(custom_access_test, CustomAccessArmorWear) {
    MockCustomAccessArmorWear mock;
    traits::CustomAccessArmorWear<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_armor;
    TestType type{
        Name{default_name},
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) armor = traits::accessArmorWear::get(type);
    decltype(auto) armor_const = traits::accessArmorWear::get(std::as_const(type));

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;
    armor = traits::accessArmorWear::get(type);

    EXPECT_EQ(armor, default_armor_change);
}
