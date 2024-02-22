#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessRestoreEffects.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_name_change = "TestName121234123556426354376585856858357858356883465";

const auto default_restoreEffects = EffectTypeContainer{EffectType::Freeze};
const auto default_restoreEffects_change = EffectTypeContainer{EffectType::Devour};

TEST(custom_access_test, AccessRestoreEffects) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_restoreEffects};

    decltype(auto) restoreEffects = type.getRestoreEffects();
    decltype(auto) restoreEffects_const = std::as_const(type).getRestoreEffects();

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
    restoreEffects = type.getRestoreEffects();

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}

TEST(custom_access_test, CustomAccessRestoreEffects) {
    MockCustomAccessRestoreEffects mock;
    traits::CustomAccessRestoreEffects<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_restoreEffects;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        result,
        5.0f,
        12};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) restoreEffects = traits::accessRestoreEffects::get(type);
    decltype(auto) restoreEffects_const = traits::accessRestoreEffects::get(std::as_const(type));

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
    restoreEffects = traits::accessRestoreEffects::get(type);

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}
