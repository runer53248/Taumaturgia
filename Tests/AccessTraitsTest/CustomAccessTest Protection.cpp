#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessProtection.hpp"

constexpr auto default_name = "TestName";
const auto default_protection = Protection{10};
const auto default_protection_change = Protection{100};

TEST(custom_access_test, AccessProtection) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        default_protection};

    decltype(auto) protection = type.getProtection();
    decltype(auto) protection_const = std::as_const(type).getProtection();

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = type.getProtection();

    EXPECT_EQ(protection, default_protection_change);
}

TEST(custom_access_test, CustomAccessProtection) {
    MockCustomAccessProtection mock;
    traits::CustomAccessProtection<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_protection;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) protection = traits::accessProtection::get(type);
    decltype(auto) protection_const = traits::accessProtection::get(std::as_const(type));

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = traits::accessProtection::get(type);

    EXPECT_EQ(protection, default_protection_change);
}
