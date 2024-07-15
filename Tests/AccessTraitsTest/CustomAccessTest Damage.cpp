#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessDamage.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

class Damage_Fixture : public Test {
public:
    Damage default_damage;
    Damage default_damage_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessDamageMock<TestType> customMock;

protected:
    void SetUp() override {
        default_damage = Damage{10};
        default_damage_change = Damage{100};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ std::ignore,
            /*Wearing*/ std::ignore,
            /*Damaging*/ default_damage,
            /*Protecting*/ std::ignore,
            /*Healing*/ std::ignore,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessDamageMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessDamageMock<TestType>::mock = nullptr;
    }
};

#ifndef NO_PREMADE_PROPERTIES
TEST_F(Damage_Fixture, Access_by_getDamage) {
    decltype(auto) damage = (*type).getDamage();
    decltype(auto) damage_const = std::as_const((*type)).getDamage();

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = (*type).getDamage();

    EXPECT_EQ(damage, default_damage_change);
}
#endif

TEST_F(Damage_Fixture, Access_by_trait_accessDamage_with_CustomAccessDamage) {
#ifndef NO_PREMADE_PROPERTIES
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_damage));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_damage));
#endif

    decltype(auto) damage = trait<Damage>::get((*type));
    decltype(auto) damage_const = trait<Damage>::get(std::as_const((*type)));

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = trait<Damage>::get((*type));

    EXPECT_EQ(damage, default_damage_change);
}
