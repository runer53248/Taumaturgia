#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessType.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_name_change = "TestName121234123556426354376585856858357858356883465";

const auto default_userType = 15.0f;
const auto default_userType_change = 12.45f;
const auto default_userType2 = 20;
const auto default_userType2_change = 45;

TEST(custom_access_test, AccessUserType) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_userType,
        default_userType2,
        std::ignore};

    decltype(auto) userType = type.getType<float>();
    decltype(auto) userType_const = std::as_const(type).getType<float>();

    decltype(auto) userType2 = type.getType<int>();
    decltype(auto) userType2_const = std::as_const(type).getType<int>();

    EXPECT_EQ(userType, default_userType);
    EXPECT_EQ(userType_const, default_userType);

    EXPECT_EQ(userType2, default_userType2);
    EXPECT_EQ(userType2_const, default_userType2);

    userType = default_userType_change;
    userType = type.getType<float>();

    userType2 = default_userType2_change;
    userType2 = type.getType<int>();

    auto test = type.getType<bool>();
    EXPECT_EQ(test, false);

    EXPECT_EQ(userType, default_userType_change);
    EXPECT_EQ(userType2, default_userType2_change);
}
