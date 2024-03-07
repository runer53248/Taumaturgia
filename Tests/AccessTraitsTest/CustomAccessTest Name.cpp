#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "TestType.hpp"

#include "Mocks/MockCustomAccessName.hpp"

using namespace testing;

class Name_Fixture : public Test {
public:
    constexpr static auto default_float = 1.2f;
    constexpr static auto default_int = 5;
    constexpr static auto default_bool = true;
    constexpr static auto default_name_ = "TestName";
    constexpr static auto default_name_change_ = "TestName121234123556426354376585856858357858356883465";
    Name default_name;
    Name default_name_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomMock<TestType> customMock;

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

        static_assert(traits::GetNameAccessable<decltype(*type)>);
        static_assert(traits::GetNameAccessable<decltype(std::as_const(*type))>);
        static_assert(traits::CustomNameAccessable<decltype(*type)>);
        static_assert(traits::CustomNameAccessable<decltype(std::as_const(*type))>);

        CustomMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomMock<TestType>::mock = nullptr;
    }
};

TEST_F(Name_Fixture, Access_by_getName) {
    decltype(auto) name = (*type).getName();
    decltype(auto) name_const = std::as_const((*type)).getName();

    EXPECT_EQ(name, default_name);
    EXPECT_EQ(name_const, default_name);

    name = default_name_change;
    name = (*type).getName();

    EXPECT_EQ(name, default_name_change);
}

TEST_F(Name_Fixture, Access_by_trait_accessName_with_CustomAccessName) {
    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_name));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_name));

    decltype(auto) name = traits::accessName::get((*type));
    decltype(auto) name_const = traits::accessName::get(std::as_const((*type)));

    EXPECT_EQ(name, default_name);
    EXPECT_EQ(name_const, default_name);

    name = default_name_change;
    name = traits::accessName::get((*type));

    EXPECT_EQ(name, default_name_change);
}
