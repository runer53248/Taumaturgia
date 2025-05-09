#include <gtest/gtest.h>
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Usage/DefaultStrategies.hpp"

using namespace testing;

struct MyType {};
using UserTestType = UserProperty<Name, MyType>;
using TestType = UserTestType;

#include "Mocks/MockCustomAccessType.hpp"

class UserProperty_Fixture : public Test {
public:
    Name default_name;
    std::unique_ptr<UserTestType> type{nullptr};
    std::unique_ptr<const UserTestType> c_type{nullptr};

    traits::CustomAccessType<Name, UserTestType> customMock;

protected:
    void SetUp() override {
        default_name = Name{"TestName"};
        type = std::make_unique<UserTestType>(default_name);
        c_type = std::make_unique<const UserTestType>(default_name);

        traits::CustomAccessType<Name, UserTestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;
        c_type = nullptr;

        traits::CustomAccessType<Name, UserTestType>::mock = nullptr;
    }
};

auto& operator<<(std::ostream& stream, const Name& name) {
    return stream << std::string(name);
}

TEST_F(UserProperty_Fixture, Access_by_trait_accessType_with_CustomAccessType) {
    EXPECT_CALL(customMock, get_(An<UserTestType&>())).Times(1).WillRepeatedly(ReturnRef(default_name));
    EXPECT_CALL(customMock, get_(An<const UserTestType&>())).Times(1).WillRepeatedly(ReturnRef(default_name));

    decltype(auto) name = trait<Name>::get((*type));
    decltype(auto) name_const = trait<Name>::get(std::as_const((*type)));

    static_assert(getType_template_able<decltype((*type)), Name>);
    static_assert(CustomAccessType_able<decltype((*type)), Name>);

    static_assert(getType_template_able<decltype(std::as_const((*type))), Name>);
    static_assert(CustomAccessType_able<decltype(std::as_const((*type))), Name>);

    static_assert(getType_template_able<decltype((*c_type)), Name>);
    static_assert(CustomAccessType_able<decltype((*c_type)), Name>);
    static_assert(getType_template_able<decltype(std::as_const((*c_type))), Name>);
    static_assert(CustomAccessType_able<decltype(std::as_const((*c_type))), Name>);

    EXPECT_EQ(name, Name{default_name});
    EXPECT_EQ(name_const, Name{default_name});
}
