#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessHealth.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_hp = Health{10};
constexpr auto default_hp_change = Health{100};

TEST(custom_access_test, AccessHealth) {
    TestType type{
        Name{default_name},
        default_hp};

    decltype(auto) hp = type.getHealth();
    decltype(auto) hp_const = std::as_const(type).getHealth();

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = type.getHealth();

    EXPECT_EQ(hp, default_hp_change);
}

TEST(custom_access_test, CustomAccessHealth) {
    MockCustomAccessHealth mock;
    traits::CustomAccessHealth<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_hp;
    TestType type{
        Name{default_name},
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) hp = traits::accessHealth::get(type);
    decltype(auto) hp_const = traits::accessHealth::get(std::as_const(type));

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = traits::accessHealth::get(type);

    EXPECT_EQ(hp, default_hp_change);
}
