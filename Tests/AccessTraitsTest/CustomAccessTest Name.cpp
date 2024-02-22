#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessName.hpp"

constexpr auto default_name = "TestName";
constexpr auto default_name_change = "TestName121234123556426354376585856858357858356883465";

TEST(custom_access_test, AccessName) {
    TestType type{Name{default_name}};

    decltype(auto) name = type.getName();
    decltype(auto) name_const = std::as_const(type).getName();

    EXPECT_EQ(name, Name{default_name});
    EXPECT_EQ(name_const, Name{default_name});
}

TEST(custom_access_test, AccessName_changeName) {
    TestType type{Name{default_name}};

    decltype(auto) name = type.getName();
    name = Name{default_name_change};
    name = type.getName();

    EXPECT_EQ(name, Name{default_name_change});
}

TEST(custom_access_test, CustomAccessName) {
    MockCustomAccessName mock;
    traits::CustomAccessName<TestType>::mock = &mock;
    using namespace testing;

    auto result = Name{default_name};
    TestType type{result};

    EXPECT_CALL(mock, get(_)).Times(1).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) name = traits::accessName::get(type);
    decltype(auto) name_const = traits::accessName::get(std::as_const(type));

    EXPECT_EQ(name, Name{default_name});
    EXPECT_EQ(name_const, Name{default_name});
}

TEST(custom_access_test, CustomAccessName_changeName) {
    MockCustomAccessName mock;
    traits::CustomAccessName<TestType>::mock = &mock;
    using namespace testing;

    auto result = Name{default_name};
    TestType type{result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));

    decltype(auto) name = traits::accessName::get(type);

    name = Name{default_name_change};
    name = traits::accessName::get(type);

    EXPECT_EQ(name, Name{default_name_change});
}
