#include <gtest/gtest.h>
#include "Usage/DefaultStrategies.hpp"

#include "TestType.hpp"

#include "Mocks/MockCustomAccessArmorWear.hpp"

using namespace testing;

constinit const auto default_name = "TestName";
constinit const auto default_float = 1.2f;
constinit const auto default_int = 5;
constinit const auto default_bool = true;

class ArmorWear_Fixture : public Test {
public:
    WearContainer default_armor;
    WearContainer default_armor_change;
    std::unique_ptr<TestType> type{nullptr};

    CustomAccessArmorWearMock<TestType> customMock;

protected:
    void SetUp() override {
        default_armor = WearContainer{10};
        default_armor_change = WearContainer{100};
        type = std::make_unique<TestType>(
            /*Naming*/ Name{default_name},
            /*Living*/ std::ignore,
            /*Wearing*/ default_armor,
            /*Damaging*/ std::ignore,
            /*Protecting*/ std::ignore,
            /*Healing*/ std::ignore,
            /*Restoring*/ std::ignore,
            /*float*/ default_float,
            /*int*/ default_int,
            /*bool*/ default_bool);

        CustomAccessArmorWearMock<TestType>::mock = &customMock;
    }

    void TearDown() override {
        type = nullptr;

        CustomAccessArmorWearMock<TestType>::mock = nullptr;
    }
};

TEST_F(ArmorWear_Fixture, Access_by_getArmorWear_or_getType) {
#ifndef NO_PREMADE_PROPERTIES
    decltype(auto) armor = (*type).getArmorWear();
    decltype(auto) armor_const = std::as_const(*type).getArmorWear();
#else
    decltype(auto) armor = (*type).getType<WearContainer>();
    decltype(auto) armor_const = std::as_const(*type).getType<WearContainer>();
#endif

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(armor)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(armor_const)>>);

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;

#ifndef NO_PREMADE_PROPERTIES
    armor = (*type).getArmorWear();
#else
    armor = (*type).getType<WearContainer>();
#endif

    EXPECT_EQ(armor, default_armor_change);
}

TEST_F(ArmorWear_Fixture, Access_by_trait_accessArmorWear_with_CustomAccessType) {
    static_assert(CustomAccessType_able<TestType, WearContainer>);

    EXPECT_CALL(customMock, get_(An<TestType&>())).Times(2).WillRepeatedly(ReturnRef(default_armor));
    EXPECT_CALL(customMock, get_(An<const TestType&>())).Times(1).WillRepeatedly(ReturnRef(default_armor));

    decltype(auto) armor = trait<WearContainer>::get(*type);
    decltype(auto) armor_const = trait<WearContainer>::get(std::as_const(*type));

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(armor)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(armor_const)>>);

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;
    armor = trait<WearContainer>::get(*type);

    EXPECT_EQ(armor, default_armor_change);
}

TEST_F(ArmorWear_Fixture, Access_by_getType) {
    decltype(auto) f = (*type).getType<float>();
    decltype(auto) c_f = std::as_const(*type).getType<float>();
    decltype(auto) i = (*type).getType<int>();
    decltype(auto) c_i = std::as_const(*type).getType<int>();
    decltype(auto) b = (*type).getType<bool>();
    decltype(auto) c_b = std::as_const(*type).getType<bool>();

    static_assert(not std::is_const_v<std::remove_reference_t<decltype(f)>>);
    static_assert(not std::is_const_v<std::remove_reference_t<decltype(i)>>);
    static_assert(not std::is_const_v<std::remove_reference_t<decltype(b)>>);

    static_assert(std::is_const_v<std::remove_reference_t<decltype(c_f)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(c_i)>>);
    static_assert(std::is_const_v<std::remove_reference_t<decltype(c_b)>>);

    EXPECT_TRUE(f == default_float);
    EXPECT_TRUE(i == default_int);
    EXPECT_TRUE(b == default_bool);

    EXPECT_TRUE(c_f == default_float);
    EXPECT_TRUE(c_i == default_int);
    EXPECT_TRUE(c_b == default_bool);
}
