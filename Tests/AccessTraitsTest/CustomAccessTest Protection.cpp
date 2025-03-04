#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessProtection.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

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

TEST_F(Protection_Fixture, Access_by_getProtection) {
#ifndef NO_PREMADE_PROPERTIES
    decltype(auto) protection = (*type).getProtection();
    decltype(auto) protection_const = std::as_const((*type)).getProtection();
#else
    decltype(auto) protection = (*type).getType<Protection>();
    decltype(auto) protection_const = std::as_const((*type)).getType<Protection>();
#endif

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
#ifndef NO_PREMADE_PROPERTIES
    protection = (*type).getProtection();
#else
    protection = (*type).getType<Protection>();
#endif

    EXPECT_EQ(protection, default_protection_change);
}

TEST_F(Protection_Fixture, Access_by_trait_accessProtection_with_CustomAccessProtection) {
    static_assert(traits::helpers::CustomTypeAccessable<TestType, Protection>);

    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_protection));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_protection));

    decltype(auto) protection = trait<Protection>::get((*type));
    decltype(auto) protection_const = trait<Protection>::get(std::as_const((*type)));

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = trait<Protection>::get((*type));

    EXPECT_EQ(protection, default_protection_change);
}
