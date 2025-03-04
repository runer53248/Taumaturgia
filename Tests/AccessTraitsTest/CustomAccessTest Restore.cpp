#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessRestoreEffects.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

class RestoreEffects_Fixture : public Test {
public:
    EffectTypeContainer default_restoreEffects;
    EffectTypeContainer default_restoreEffects_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessRestoreEffectsMock<TestType> customMock;

protected:
    void SetUp() override {
        default_restoreEffects = EffectTypeContainer{EffectType::Freeze};
        default_restoreEffects_change = EffectTypeContainer{EffectType::Devour};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ std::ignore,
            /*Wearing*/ std::ignore,
            /*Damaging*/ std::ignore,
            /*Protecting*/ std::ignore,
            /*Healing*/ std::ignore,
            /*Restoring*/ default_restoreEffects,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessRestoreEffectsMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessRestoreEffectsMock<TestType>::mock = nullptr;
    }
};

TEST_F(RestoreEffects_Fixture, Access_by_getRestoreEffects) {
#ifndef NO_PREMADE_PROPERTIES
    decltype(auto) restoreEffects = (*type).getRestoreEffects();
    decltype(auto) restoreEffects_const = std::as_const((*type)).getRestoreEffects();
#else
    decltype(auto) restoreEffects = (*type).getType<EffectTypeContainer>();
    decltype(auto) restoreEffects_const = std::as_const((*type)).getType<EffectTypeContainer>();
#endif

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
#ifndef NO_PREMADE_PROPERTIES
    restoreEffects = (*type).getRestoreEffects();
#else
    restoreEffects = (*type).getType<EffectTypeContainer>();
#endif

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}

TEST_F(RestoreEffects_Fixture, Access_by_trait_accessRestoreEffects_with_CustomAccessRestoreEffects) {
    static_assert(traits::helpers::CustomTypeAccessable<TestType, EffectTypeContainer>);

    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_restoreEffects));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_restoreEffects));

    decltype(auto) restoreEffects = trait<EffectTypeContainer>::get((*type));
    decltype(auto) restoreEffects_const = trait<EffectTypeContainer>::get(std::as_const((*type)));

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
    restoreEffects = trait<EffectTypeContainer>::get((*type));

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}
