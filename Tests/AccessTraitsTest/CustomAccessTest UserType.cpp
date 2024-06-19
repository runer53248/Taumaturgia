#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessType.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit type_1 default_type_1 = 15.0f; // not const because it will be returned as reference - '...WillRepeatedly(ReturnRef(default_type_1));'
constinit const type_1 default_type_1_change = 12.45f;
constinit const type_2 default_type_2 = 20;
constinit const type_2 default_type_2_change = 45;
constinit const type_3 default_type_3 = true;
constinit const type_3 default_type_3_change = false;

class UserType_with_UserProperty_Fixture : public Test {
public:
    std::unique_ptr<TestType> type{nullptr};

    traits::CustomAccessType<type_1, TestType> customMock;

protected:
    void SetUp() override {
        type = std::make_unique<TestType>(
            Name{default_name},
            std::ignore,
            std::ignore,
            std::ignore,
            std::ignore,
            std::ignore,
            std::ignore,
            default_type_1,
            default_type_2,
            default_type_3);

        traits::CustomAccessType<type_1, TestType> mock;
        traits::CustomAccessType<type_1, TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        traits::CustomAccessType<type_1, TestType>::mock = nullptr;
    }
};

TEST_F(UserType_with_UserProperty_Fixture, Access_by_getType) {
    decltype(auto) userType = (*type).getType<type_1>();
    decltype(auto) userType_const = std::as_const((*type)).getType<type_1>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType_const)>>);

    EXPECT_EQ(userType, default_type_1);
    EXPECT_EQ(userType_const, default_type_1);

    decltype(auto) userType2 = (*type).getType<type_2>();
    decltype(auto) userType2_const = std::as_const((*type)).getType<type_2>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType2)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType2_const)>>);

    EXPECT_EQ(userType2, default_type_2);
    EXPECT_EQ(userType2_const, default_type_2);

    decltype(auto) userType3 = (*type).getType<type_3>();
    decltype(auto) userType3_const = std::as_const((*type)).getType<type_3>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType3)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType3_const)>>);

    EXPECT_EQ(userType3, default_type_3);
    EXPECT_EQ(userType3_const, default_type_3);

    userType = default_type_1_change;
    userType = (*type).getType<type_1>();

    EXPECT_EQ(userType, default_type_1_change);

    userType2 = default_type_2_change;
    userType2 = (*type).getType<type_2>();

    EXPECT_EQ(userType2, default_type_2_change);

    userType3 = default_type_3_change;
    userType3 = (*type).getType<type_3>();

    EXPECT_EQ(userType3, default_type_3_change);
}

TEST_F(UserType_with_UserProperty_Fixture, Access_by_trait_accessType_with_CustomAccessType) {
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_type_1));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_type_1));

    decltype(auto) userType = traits::accessType<type_1>::get((*type));
    decltype(auto) userType_const = traits::accessType<type_1>::get(std::as_const((*type)));

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType_const)>>);

    EXPECT_EQ(userType, default_type_1);
    EXPECT_EQ(userType_const, default_type_1);

    userType = default_type_1_change;
    userType = traits::accessType<type_1>::get((*type));

    EXPECT_EQ(userType, default_type_1_change);
}
