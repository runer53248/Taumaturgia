#include <gtest/gtest.h>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/Properties/UserProperty.hpp"

struct MyType {};

template <typename TYPE>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<TYPE, T>;
};

using TestType = add_properties<
    MyType,
    //
    UserPropertyAdapter<float>::type,  // not on order_list - last on c-tor arguments list
    UserPropertyAdapter<int>::type,    // not on order_list - always apply to MyType as most inner (before Naming !!!)
    UserPropertyAdapter<bool>::type,
    // so its first argument in TestType c-tor
    //
    // all below are in correct order in TestType c-tor arguments but take name as they first argument so its looks like Naming is before them
    Living,
    Wearing,
    Protecting,  // even if switch order they return the same type
    Damaging,    //
    Healing,
    Restoring,
    Naming  // most inner to add (apply to type after unordered/unknown properties)
    // actualy last but other requires that it exist in type to add name from they own c-tors.
    >;

// C-tor args order
//
// TestType(
//     Naming, // c-tors move it in front because its required (its added to MyType as last of ordered types)
//     Living,
//     Wearing,
//     Damaging,
//     Protecting,
//     Healing,
//     Restoring,
//     UserProperty<float>, // because the are unordered (order at add_properties arguments is used)
//     UserProperty<int>)

#include "Mocks/MockCustomAccessArmorWear.hpp"
#include "Mocks/MockCustomAccessCureHealth.hpp"
#include "Mocks/MockCustomAccessDamage.hpp"
#include "Mocks/MockCustomAccessHealth.hpp"
#include "Mocks/MockCustomAccessName.hpp"
#include "Mocks/MockCustomAccessProtection.hpp"
#include "Mocks/MockCustomAccessRestoreEffects.hpp"
#include "Mocks/MockCustomAccessType.hpp"

std::ostream& operator<<(std::ostream& stream, const Name& name) {
  return stream << std::string(name);
}

/////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////

constexpr auto default_hp = Health{10};
constexpr auto default_hp_change = Health{100};

TEST(custom_access_test, AccessHealth) {
    TestType type{
        Name{default_name},
        default_hp};

    decltype(auto) hp = type.getHealth();
    decltype(auto) hp_const = std::as_const(type).getHealth();

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = type.getHealth();

    EXPECT_EQ(hp, default_hp_change);
}

TEST(custom_access_test, CustomAccessHealth) {
    MockCustomAccessHealth mock;
    traits::CustomAccessHealth<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_hp;
    TestType type{
        Name{default_name},
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) hp = traits::accessHealth::get(type);
    decltype(auto) hp_const = traits::accessHealth::get(std::as_const(type));

    EXPECT_EQ(hp, default_hp);
    EXPECT_EQ(hp_const, default_hp);

    hp = default_hp_change;
    hp = traits::accessHealth::get(type);

    EXPECT_EQ(hp, default_hp_change);
}
/////////////////////////////////////////////////////////

const auto default_armor = ProtectionContainer{10};
const auto default_armor_change = ProtectionContainer{100};

TEST(custom_access_test, AccessArmorWear) {
    TestType type{
        Name{default_name},
        std::ignore,
        default_armor};

    decltype(auto) armor = type.getArmorWear();
    decltype(auto) armor_const = std::as_const(type).getArmorWear();

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;
    armor = type.getArmorWear();

    EXPECT_EQ(armor, default_armor_change);
}

TEST(custom_access_test, CustomAccessArmorWear) {
    MockCustomAccessArmorWear mock;
    traits::CustomAccessArmorWear<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_armor;
    TestType type{
        Name{default_name},
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) armor = traits::accessArmorWear::get(type);
    decltype(auto) armor_const = traits::accessArmorWear::get(std::as_const(type));

    EXPECT_EQ(armor, default_armor);
    EXPECT_EQ(armor_const, default_armor);

    armor = default_armor_change;
    armor = traits::accessArmorWear::get(type);

    EXPECT_EQ(armor, default_armor_change);
}

/////////////////////////////////////////////////////////

constexpr auto default_damage = Damage{10};
constexpr auto default_damage_change = Damage{100};

TEST(custom_access_test, AccessDamage) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        default_damage};

    decltype(auto) damage = type.getDamage();
    decltype(auto) damage_const = std::as_const(type).getDamage();

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = type.getDamage();

    EXPECT_EQ(damage, default_damage_change);
}

TEST(custom_access_test, CustomAccessDamage) {
    MockCustomAccessDamage mock;
    traits::CustomAccessDamage<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_damage;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) damage = traits::accessDamage::get(type);
    decltype(auto) damage_const = traits::accessDamage::get(std::as_const(type));

    EXPECT_EQ(damage, default_damage);
    EXPECT_EQ(damage_const, default_damage);

    damage = default_damage_change;
    damage = traits::accessDamage::get(type);

    EXPECT_EQ(damage, default_damage_change);
}

/////////////////////////////////////////////////////////

const auto default_protection = Protection{10};
const auto default_protection_change = Protection{100};

TEST(custom_access_test, AccessProtection) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        default_protection};

    decltype(auto) protection = type.getProtection();
    decltype(auto) protection_const = std::as_const(type).getProtection();

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = type.getProtection();

    EXPECT_EQ(protection, default_protection_change);
}

TEST(custom_access_test, CustomAccessProtection) {
    MockCustomAccessProtection mock;
    traits::CustomAccessProtection<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_protection;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) protection = traits::accessProtection::get(type);
    decltype(auto) protection_const = traits::accessProtection::get(std::as_const(type));

    EXPECT_EQ(protection, default_protection);
    EXPECT_EQ(protection_const, default_protection);

    protection = default_protection_change;
    protection = traits::accessProtection::get(type);

    EXPECT_EQ(protection, default_protection_change);
}

/////////////////////////////////////////////////////////

constexpr auto default_cureHp = CureHealth{10};
constexpr auto default_cureHp_change = CureHealth{100};

TEST(custom_access_test, AccessCureHealth) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_cureHp};

    decltype(auto) cureHp = type.getCureHealth();
    decltype(auto) cureHp_const = std::as_const(type).getCureHealth();

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = type.getCureHealth();

    EXPECT_EQ(cureHp, default_cureHp_change);
}

TEST(custom_access_test, CustomAccessCureHealth) {
    MockCustomAccessCureHealth mock;
    traits::CustomAccessCureHealth<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_cureHp;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        result};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) cureHp = traits::accessCureHealth::get(type);
    decltype(auto) cureHp_const = traits::accessCureHealth::get(std::as_const(type));

    EXPECT_EQ(cureHp, default_cureHp);
    EXPECT_EQ(cureHp_const, default_cureHp);

    cureHp = default_cureHp_change;
    cureHp = traits::accessCureHealth::get(type);

    EXPECT_EQ(cureHp, default_cureHp_change);
}

/////////////////////////////////////////////////////////

const auto default_restoreEffects = EffectTypeContainer{EffectType::Freeze};
const auto default_restoreEffects_change = EffectTypeContainer{EffectType::Devour};

TEST(custom_access_test, AccessRestoreEffects) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_restoreEffects};

    decltype(auto) restoreEffects = type.getRestoreEffects();
    decltype(auto) restoreEffects_const = std::as_const(type).getRestoreEffects();

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
    restoreEffects = type.getRestoreEffects();

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}

TEST(custom_access_test, CustomAccessRestoreEffects) {
    MockCustomAccessRestoreEffects mock;
    traits::CustomAccessRestoreEffects<TestType>::mock = &mock;
    using namespace testing;

    auto result = default_restoreEffects;
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        result,
        5.0f,
        12};

    EXPECT_CALL(mock, get(_)).Times(2).WillRepeatedly(ReturnRef(result));
    EXPECT_CALL(mock, getConst(_)).Times(1).WillRepeatedly(ReturnRef(result));

    decltype(auto) restoreEffects = traits::accessRestoreEffects::get(type);
    decltype(auto) restoreEffects_const = traits::accessRestoreEffects::get(std::as_const(type));

    EXPECT_EQ(restoreEffects, default_restoreEffects);
    EXPECT_EQ(restoreEffects_const, default_restoreEffects);

    restoreEffects = default_restoreEffects_change;
    restoreEffects = traits::accessRestoreEffects::get(type);

    EXPECT_EQ(restoreEffects, default_restoreEffects_change);
}

/////////////////////////////////////////////////////////

const auto default_userType = 15.0f;
const auto default_userType_change = 12.45f;
const auto default_userType2 = 20;
const auto default_userType2_change = 45;

TEST(custom_access_test, AccessUserType) {
    TestType type{
        Name{default_name},
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        std::ignore,
        default_userType,
        default_userType2,
        std::ignore};

    decltype(auto) userType = type.getType<float>();
    decltype(auto) userType_const = std::as_const(type).getType<float>();

    decltype(auto) userType2 = type.getType<int>();
    decltype(auto) userType2_const = std::as_const(type).getType<int>();

    EXPECT_EQ(userType, default_userType);
    EXPECT_EQ(userType_const, default_userType);

    EXPECT_EQ(userType2, default_userType2);
    EXPECT_EQ(userType2_const, default_userType2);

    userType = default_userType_change;
    userType = type.getType<float>();

    userType2 = default_userType2_change;
    userType2 = type.getType<int>();

    auto test = type.getType<bool>();
    EXPECT_EQ(test, false);

    EXPECT_EQ(userType, default_userType_change);
    EXPECT_EQ(userType2, default_userType2_change);
}