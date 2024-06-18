#include <gtest/gtest.h>
#include "Taumaturgia/Strategies/Defaults/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessHealth.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

class Health_Fixture : public Test {
public:
    Health default_hp;
    Health default_hp_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessHealthMock<TestType> customMock;

protected:
    void SetUp() override {
        default_hp = Health{10};
        default_hp = Health{100};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ default_hp,
            /*Wearing*/ std::ignore,
            /*Damaging*/ std::ignore,
            /*Protecting*/ std::ignore,
            /*Healing*/ std::ignore,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessHealthMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessHealthMock<TestType>::mock = nullptr;
    }
};

#ifndef NO_PREMADE_PROPERTIES
TEST_F(Health_Fixture, Access_by_getHealth) {
    decltype(auto) hp = (*type).getHealth();
    decltype(auto) hp_const = std::as_const((*type)).getHealth();

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = (*type).getHealth();

    EXPECT_EQ(hp, default_hp_change);
}
#endif

TEST_F(Health_Fixture, Access_by_trait_accessHealth_with_CustomAccessHealth) {
#ifndef NO_PREMADE_PROPERTIES
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_hp));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_hp));
#endif

    decltype(auto) hp = Livingable_trait::get((*type));
    decltype(auto) hp_const = Livingable_trait::get(std::as_const((*type)));

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = Livingable_trait::get((*type));

    EXPECT_EQ(hp, default_hp_change);
}
