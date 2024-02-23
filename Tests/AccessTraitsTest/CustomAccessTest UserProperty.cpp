#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/Properties/UserProperty.hpp"

struct MyType {};
using UserTestType = UserProperty<Name, MyType>;

#include "Mocks/MockCustomAccessType.hpp"

std::ostream& operator<<(std::ostream& stream, const Name& name) {
    return stream << std::string(name);
}

constexpr auto default_name = "TestName";

TEST(user_access_test, CustomTypeAccess_accessType) {
    MockCustomTypeAccess<Name, UserTestType> mock;
    traits::CustomTypeAccess<Name, UserTestType>::mock = &mock;
    using namespace testing;

    auto result = Name{default_name};
    UserTestType type{result};
    const UserTestType c_type{result};

    EXPECT_CALL(mock, get(_)).Times(1).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) name = traits::accessType<Name>::get(type);
    decltype(auto) name_const = traits::accessType<Name>::get(std::as_const(type));

    static_assert(traits::GetTypeAccessable<decltype(type), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(type), Name>);

    static_assert(traits::GetTypeAccessable<decltype(std::as_const(type)), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(std::as_const(type)), Name>);

    static_assert(traits::GetTypeAccessable<decltype(c_type), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(c_type), Name>);
    static_assert(traits::GetTypeAccessable<decltype(std::as_const(c_type)), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(std::as_const(c_type)), Name>);

    EXPECT_EQ(name, Name{default_name});
    EXPECT_EQ(name_const, Name{default_name});
}
