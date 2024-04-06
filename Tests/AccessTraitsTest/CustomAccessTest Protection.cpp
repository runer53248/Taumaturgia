#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessProtection.hpp"

using namespace testing;

constinit auto default_name = "TestName";
constinit auto default_float = 1.2f;
constinit auto default_int = 5;
constinit auto default_bool = true;

class Protection_Fixture : public Test {
public:
    Protection default_protection;
    Protection default_protection_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessProtectionMock<TestType> customMock;

protected:
    void SetUp() override {
        default_protection = Protection{10};
        default_protection_change = Protection{100};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ std::ignore,
            /*Wearing*/ std::ignore,
            /*Damaging*/ std::ignore,
            /*Protecting*/ default_protection,
            /*Healing*/ std::ignore,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessProtectionMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessProtectionMock<TestType>::mock = nullptr;
    }
};

#ifndef NO_PREMADE_PROPERTIES
TEST_F(Protection_Fixture, Access_by_getProtection) {
    decltype(auto) protection = (*type).getProtection();
    decltype(auto) protection_const = std::as_const((*type)).getProtection();

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = (*type).getProtection();

    EXPECT_EQ(protection, default_protection_change);
}
#endif

TEST_F(Protection_Fixture, Access_by_trait_accessProtection_with_CustomAccessProtection) {
#ifndef NO_PREMADE_PROPERTIES
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_protection));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_protection));
#endif

    decltype(auto) protection = traits::accessProtection::get((*type));
    decltype(auto) protection_const = traits::accessProtection::get(std::as_const((*type)));

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = traits::accessProtection::get((*type));

    EXPECT_EQ(protection, default_protection_change);
}
