#include <gtest/gtest.h>
#include "Taumaturgia/Object/DefaultStrategies.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

using namespace testing;

struct MyType {};
using UserTestType = UserProperty<Name, MyType>;

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

    decltype(auto) name = traits::accessType<Name>::get((*type));
    decltype(auto) name_const = traits::accessType<Name>::get(std::as_const((*type)));

    static_assert(traits::GetTypeAccessable<decltype((*type)), Name>);
    static_assert(traits::CustomTypeAccessable<decltype((*type)), Name>);

    static_assert(traits::GetTypeAccessable<decltype(std::as_const((*type))), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(std::as_const((*type))), Name>);

    static_assert(traits::GetTypeAccessable<decltype((*c_type)), Name>);
    static_assert(traits::CustomTypeAccessable<decltype((*c_type)), Name>);
    static_assert(traits::GetTypeAccessable<decltype(std::as_const((*c_type))), Name>);
    static_assert(traits::CustomTypeAccessable<decltype(std::as_const((*c_type))), Name>);

    EXPECT_EQ(name, Name{default_name});
    EXPECT_EQ(name_const, Name{default_name});
}
