#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessCureHealth.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_cureHp = CureHealth{10};
constexpr auto default_cureHp_change = CureHealth{100};

TEST(custom_access_test, AccessCureHealth) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_cureHp};

    decltype(auto) cureHp = type.getCureHealth();
    decltype(auto) cureHp_const = std::as_const(type).getCureHealth();

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = type.getCureHealth();

    EXPECT_EQ(cureHp, default_cureHp_change);
}

TEST(custom_access_test, CustomAccessCureHealth) {
    MockCustomAccessCureHealth mock;
    traits::CustomAccessCureHealth<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_cureHp;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) cureHp = traits::accessCureHealth::get(type);
    decltype(auto) cureHp_const = traits::accessCureHealth::get(std::as_const(type));

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = traits::accessCureHealth::get(type);

    EXPECT_EQ(cureHp, default_cureHp_change);
}
