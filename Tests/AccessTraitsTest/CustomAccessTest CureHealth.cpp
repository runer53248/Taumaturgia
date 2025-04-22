#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessCureHealth.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

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

TEST_F(CureHealth_Fixture, Access_by_getCureHealth) {
#ifndef NO_PREMADE_PROPERTIES
    decltype(auto) cureHp = (*type).getCureHealth();
    decltype(auto) cureHp_const = std::as_const((*type)).getCureHealth();
#else
    decltype(auto) cureHp = (*type).getType<CureHealth>();
    decltype(auto) cureHp_const = std::as_const((*type)).getType<CureHealth>();
#endif

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(cureHp)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(cureHp_const)>>);

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
#ifndef NO_PREMADE_PROPERTIES
    cureHp = (*type).getCureHealth();
#else
    cureHp = (*type).getType<CureHealth>();
#endif

    EXPECT_EQ(cureHp, default_cureHp_change);
}

TEST_F(CureHealth_Fixture, Access_by_trait_accessCureHealth_with_CustomAccessCureHealth) {
    static_assert(CustomAccessType_able<TestType, CureHealth>);

    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_cureHp));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_cureHp));

    decltype(auto) cureHp = trait<CureHealth>::get((*type));
    decltype(auto) cureHp_const = trait<CureHealth>::get(std::as_const((*type)));

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(cureHp)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(cureHp_const)>>);

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = trait<CureHealth>::get((*type));

    EXPECT_EQ(cureHp, default_cureHp_change);
}
