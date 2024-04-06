#include <gtest/gtest.h>
#include "Taumaturgia/Strategies/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessCureHealth.hpp"

using namespace testing;

constinit auto default_name = "TestName";
constinit auto default_float = 1.2f;
constinit auto default_int = 5;
constinit auto default_bool = true;

class CureHealth_Fixture : public Test {
public:
    CureHealth default_cureHp;
    CureHealth default_cureHp_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessCureHealthMock<TestType> customMock;

protected:
    void SetUp() override {
        default_cureHp = CureHealth{10};
        default_cureHp_change = CureHealth{100};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ std::ignore,
            /*Wearing*/ std::ignore,
            /*Damaging*/ std::ignore,
            /*Protecting*/ std::ignore,
            /*Healing*/ default_cureHp,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessCureHealthMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessCureHealthMock<TestType>::mock = nullptr;
    }
};

#ifndef NO_PREMADE_PROPERTIES
TEST_F(CureHealth_Fixture, Access_by_getCureHealth) {
    decltype(auto) cureHp = (*type).getCureHealth();
    decltype(auto) cureHp_const = std::as_const((*type)).getCureHealth();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(cureHp)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(cureHp_const)>>);

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = (*type).getCureHealth();

    EXPECT_EQ(cureHp, default_cureHp_change);
}
#endif

TEST_F(CureHealth_Fixture, Access_by_trait_accessCureHealth_with_CustomAccessCureHealth) {
#ifndef NO_PREMADE_PROPERTIES
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_cureHp));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_cureHp));
#endif

    decltype(auto) cureHp = traits::accessCureHealth::get((*type));
    decltype(auto) cureHp_const = traits::accessCureHealth::get(std::as_const((*type)));

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(cureHp)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(cureHp_const)>>);

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = traits::accessCureHealth::get((*type));

    EXPECT_EQ(cureHp, default_cureHp_change);
}
