#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessType.hpp"

using namespace testing;

constinit auto default_name = "TestName";
constinit float default_userType = 15.0f;
constinit float default_userType_change = 12.45f;
constinit int default_userType2 = 20;
constinit int default_userType2_change = 45;
constinit bool default_userType3 = true;
constinit bool default_userType3_change = false;

class UserType_with_UserProperty_Fixture : public Test {
public:
    std::unique_ptr<TestType> type{nullptr};

    traits::CustomAccessType<float, TestType> customMock;

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
            default_userType,
            default_userType2,
            default_userType3);

        traits::CustomAccessType<float, TestType> mock;
        traits::CustomAccessType<float, TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        traits::CustomAccessType<float, TestType>::mock = nullptr;
    }
};

TEST_F(UserType_with_UserProperty_Fixture, Access_by_getType) {
    decltype(auto) userType = (*type).getType<float>();
    decltype(auto) userType_const = std::as_const((*type)).getType<float>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType_const)>>);

    EXPECT_EQ(userType, default_userType);
    EXPECT_EQ(userType_const, default_userType);

    decltype(auto) userType2 = (*type).getType<int>();
    decltype(auto) userType2_const = std::as_const((*type)).getType<int>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType2)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType2_const)>>);

    EXPECT_EQ(userType2, default_userType2);
    EXPECT_EQ(userType2_const, default_userType2);

    decltype(auto) userType3 = (*type).getType<bool>();
    decltype(auto) userType3_const = std::as_const((*type)).getType<bool>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType3)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType3_const)>>);

    EXPECT_EQ(userType3, default_userType3);
    EXPECT_EQ(userType3_const, default_userType3);

    userType = default_userType_change;
    userType = (*type).getType<float>();

    EXPECT_EQ(userType, default_userType_change);

    userType2 = default_userType2_change;
    userType2 = (*type).getType<int>();

    EXPECT_EQ(userType2, default_userType2_change);

    userType3 = default_userType3_change;
    userType3 = (*type).getType<bool>();

    EXPECT_EQ(userType3, default_userType3_change);
}

TEST_F(UserType_with_UserProperty_Fixture, Access_by_trait_accessType_with_CustomAccessType) {
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_userType));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_userType));

    decltype(auto) userType = traits::accessType<float>::get((*type));
    decltype(auto) userType_const = traits::accessType<float>::get(std::as_const((*type)));

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(userType)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(userType_const)>>);

    EXPECT_EQ(userType, default_userType);
    EXPECT_EQ(userType_const, default_userType);

    userType = default_userType_change;
    userType = traits::accessType<float>::get((*type));

    EXPECT_EQ(userType, default_userType_change);
}
