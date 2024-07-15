#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessName.hpp"

using namespace testing;

constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;
constinit const auto default_name_ = "TestName";
constinit const auto default_name_change_ = "TestName121234123556426354376585856858357858356883465";

class Name_Fixture : public Test {
public:
    Name default_name;
    Name default_name_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessNameMock<TestType> customMock;

protected:
    void SetUp() override {
        default_name = Name{default_name_};
        default_name_change = Name{default_name_change_};
        type = std::make_unique<TestType>(
            /*Naming*/ default_name,
            /*Living*/ std::ignore,
            /*Wearing*/ std::ignore,
            /*Damaging*/ std::ignore,
            /*Protecting*/ std::ignore,
            /*Healing*/ std::ignore,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

#ifndef NO_PREMADE_PROPERTIES
        static_assert(traits::GetNameAccessable<decltype(*type)>);
        static_assert(traits::GetNameAccessable<decltype(std::as_const(*type))>);
#endif
        static_assert(traits::CustomNameAccessable<decltype(*type)>);
        static_assert(traits::CustomNameAccessable<decltype(std::as_const(*type))>);

        CustomAccessNameMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessNameMock<TestType>::mock = nullptr;
    }
};

#ifndef NO_PREMADE_PROPERTIES
TEST_F(Name_Fixture, Access_by_getName) {
    decltype(auto) name = (*type).getName();
    decltype(auto) name_const = std::as_const((*type)).getName();

    EXPECT_EQ(name, default_name);
    EXPECT_EQ(name_const, default_name);

    name = default_name_change;
    name = (*type).getName();

    EXPECT_EQ(name, default_name_change);
}
#endif

TEST_F(Name_Fixture, Access_by_trait_accessName_with_CustomAccessName) {
#ifndef NO_PREMADE_PROPERTIES
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_name));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_name));
#endif

    decltype(auto) name = trait<Name>::get((*type));
    decltype(auto) name_const = trait<Name>::get(std::as_const((*type)));

    EXPECT_EQ(name, default_name);
    EXPECT_EQ(name_const, default_name);

    name = default_name_change;
    name = trait<Name>::get((*type));

    EXPECT_EQ(name, default_name_change);
}
