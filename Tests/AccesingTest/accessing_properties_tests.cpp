#include <gtest/gtest.h>
#include <experimental/type_traits>
#include "Introduction/parse_type_name.hpp"
#include "Taumaturgia/Traits/access_features.hpp"
#include "Usage/With.hpp"

// MARK: empty, tag_health, with_health

struct empty {
    empty() = default;
    empty(auto...) {}
};
struct tag_health {};
struct tag_health2 {};
struct tag_damage {};
struct tag_wrong {};

static_assert(Property<Living>::value < Property<Damaging>::value);

struct with_health {
    using hold_type = Health;

    Health hp;
};

struct with_health_and_damage {
    // private:
    Health other_hp{};
    Damage other_dmg{};

public:
    template <size_t S, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (S == 0)
            return (self.other_hp);
        else
            return (self.other_dmg);
    }
    template <size_t S, typename Self>
        requires(S > 1)
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    template <typename Type, typename... Tags, typename Self>
        requires((std::same_as<Type, Health> or std::same_as<Type, Damage>) and sizeof...(Tags) == 0)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        if constexpr (std::same_as<Type, Health>)
            return (self.other_hp);
        if constexpr (std::same_as<Type, Damage>)
            return (self.other_dmg);
    }
    template <typename Type, typename... Tags, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;
};

// MARK: properties

template <typename T>
using MyLiving = AdvanceUserProperty<::Health, tag_health>::type<T>;
template <typename T>
using MyLiving2 = AdvanceUserProperty<::Health, tag_health2>::type<T>;
template <typename T>
using MyLiving_once = AdvanceUserProperty<::Health, tag_health>::order<T>;

template <typename T>
using MyDamaging = AdvanceUserProperty<::Damage, tag_damage>::type<T>;
template <typename T>
using MyDamaging_once = AdvanceUserProperty<::Damage, tag_damage>::order<T>;

namespace With {
[[maybe_unused]] const auto MyHealth = user_property<::Health, struct tag_health>;
[[maybe_unused]] const auto MyHealth_once = user_property_once<::Health, struct tag_health>;

[[maybe_unused]] const auto MyDamage = user_property<::Damage, struct tag_damage>;
[[maybe_unused]] const auto MyDamage_once = user_property_once<::Damage, struct tag_damage>;
}  // namespace With

static_assert(std::same_as<
              Property<MyLiving>::property_data,
              decltype(With::MyHealth)::property_data>);
static_assert(std::same_as<
              Property<MyLiving_once>::property_data,
              decltype(With::MyHealth_once)::property_data>);

static_assert(std::same_as<
              Property<MyDamaging>::property_data,
              decltype(With::MyDamage)::property_data>);
static_assert(std::same_as<
              Property<MyDamaging_once>::property_data,
              decltype(With::MyDamage_once)::property_data>);

// MARK: helpers

template <size_t N>
struct val {
    static constexpr size_t value = N;
};

template <typename T, typename N>
using member_getType = decltype(std::declval<T&>().template getType<N::value>());
template <typename T, typename TYPE, typename... Tags>
using member_getTypeTaged = decltype(std::declval<T&>().template getTypeTaged<TYPE, Tags...>());

template <typename T, typename N>
using free_getType = decltype(getType<N::value>(std::declval<T&>()));
template <typename T, typename TYPE, typename... Tags>
using free_getTypeTaged = decltype(getTypeTaged<TYPE, Tags...>(std::declval<T&>()));

template <template <typename...> typename Fn, typename TARGET, typename... CONFIG>
using detect = std::experimental::is_detected<Fn, TARGET, CONFIG...>;

// MARK: Access_Fixture

Health base_health{30};
Health taged_health{15};

Damage base_damage{10};
Damage taged_damage{100};

using namespace testing;

template <typename BASE>
class Access_Fixture : public Test {
public:
    using base = BASE;
    using type = add_properties_ordered<base, MyLiving, MyDamaging, Damaging, Living>;

    type obj_by_list = base{base_health} | (With::MyHealth | With::MyDamage | With::Damage | With::Health);           // set base value
    type obj_by_create = base{base_health} | With::MyHealth | With::MyDamage | With::Damage | With::Health | Create;  // set base value
    type obj_by_creator{};

protected:
    void SetUp() override {
        if constexpr (Livingable<base> and not Damagingable<base>) {
            // static_assert(not std::same_as<
            //               add_properties_ordered<base, MyLiving, MyDamaging, Damaging>,
            //               add_properties_ordered<base, MyLiving, MyDamaging>>);

            static_assert(std::same_as<
                          add_properties_ordered<base, MyLiving, MyDamaging, Living>,
                          add_properties_ordered<base, MyLiving, MyDamaging>>);

            static_assert(std::constructible_from<decltype(obj_by_creator), Damage&, Health&, Damage&, Health&>);
            static_assert(std::constructible_from<decltype(obj_by_creator), Damage, Health, Damage, Health&>);
            static_assert(std::constructible_from<decltype(obj_by_creator), Damage&, Health&, Damage&, Health>);
            static_assert(std::constructible_from<decltype(obj_by_creator), Damage&, Health, Damage, Health>);
            static_assert(std::constructible_from<decltype(obj_by_creator), Damage, Health&, Damage&, Health&>);
            static_assert(std::constructible_from<decltype(obj_by_creator), Damage, Health, Damage, Health>);

            type obj_by_creator_new = (From::base<base> | With::MyHealth | With::MyDamage | With::Damage | With::Health)(base_damage, taged_health, taged_damage, /*from base*/ base_health);  // set both added and base values
            obj_by_creator = obj_by_creator_new;
        } else if constexpr (std::same_as<base, with_health_and_damage>) {
            type obj_by_creator_new = (From::base<base> | With::MyHealth | With::MyDamage | With::Damage | With::Health)();  // set both added and base values
            obj_by_creator = obj_by_creator_new;
        } else {
            type obj_by_creator_new = (From::base<base> | With::MyHealth | With::MyDamage | With::Damage | With::Health)(base_health, base_damage, taged_health, taged_damage);  // set both added and base values
            obj_by_creator = obj_by_creator_new;
        }

        trait<Health>::get(obj_by_list) = taged_health;  // set added value
        if constexpr (not Livingable<base>)
            obj_by_list.template getTypeTaged<Health>() = base_health;           // set added value
        obj_by_list.template getTypeTaged<Health, tag_health>() = taged_health;  // set added value
        obj_by_list.template getTypeTaged<Damage>() = base_damage;               // set added value
        obj_by_list.template getTypeTaged<Damage, tag_damage>() = taged_damage;  // set added value

        trait<Health>::get(obj_by_create) = taged_health;  // set added value
        if constexpr (not Livingable<base>)
            obj_by_create.template getTypeTaged<Health>() = base_health;           // set added value
        obj_by_create.template getTypeTaged<Health, tag_health>() = taged_health;  // set added value
        obj_by_create.template getTypeTaged<Damage>() = base_damage;               // set added value
        obj_by_create.template getTypeTaged<Damage, tag_damage>() = taged_damage;  // set added value

        if constexpr (std::same_as<base, with_health_and_damage>) {
            obj_by_creator.template getTypeTaged<Health>() = base_health;               // set added value
            obj_by_creator.template getTypeTaged<Health, tag_health>() = taged_health;  // set added value
            obj_by_creator.template getTypeTaged<Damage>() = base_damage;               // set added value
            obj_by_creator.template getTypeTaged<Damage, tag_damage>() = taged_damage;  // set added value
        }
    }
    void TearDown() override {}
};

using Access_Fixture_empty = Access_Fixture<empty>;
using Access_Fixture_with_health = Access_Fixture<with_health>;
using Access_Fixture_with_health_and_damage = Access_Fixture<with_health_and_damage>;

// MARK: tests

TEST(extra, extra) {
    //* taged and untaged properties should be added to base without it's type accessable
    static_assert(not Livingable<empty>);
    EXPECT_TRUE((std::same_as<
                 add_properties_ordered<empty, Living_impl, MyLiving>,
                 add_properties_ordered<empty, Living, MyLiving>>));
    EXPECT_TRUE((std::same_as<
                 add_properties_ordered<empty, Living_impl, MyLiving2, MyLiving>,
                 add_properties_ordered<empty, Living, MyLiving2, MyLiving>>));

    //* shouldn't add untaged if base have it's property type accessable
    static_assert(Livingable<with_health>);
    EXPECT_FALSE((std::same_as<
                  add_properties_ordered<with_health, Living_impl, MyLiving>,
                  add_properties_ordered<with_health, Living, MyLiving>>));
    EXPECT_FALSE((std::same_as<
                  add_properties_ordered<with_health, Living_impl, MyLiving2, MyLiving>,
                  add_properties_ordered<with_health, Living, MyLiving2, MyLiving>>));

    static_assert(not Livingable<empty>);
    using test_a = add_properties_ordered<empty, Living_impl, MyLiving>;
    using test_b = add_properties_ordered<empty, Living, MyLiving>;
    using test_c = add_properties_ordered<empty, Living, MyLiving2, MyLiving>;

    static_assert(Livingable<with_health>);
    using test_a2 = add_properties_ordered<with_health, Living_impl, MyLiving>;
    using test_b2 = add_properties_ordered<with_health, Living, MyLiving>;
    using test_c2 = add_properties_ordered<with_health, Living, MyLiving2, MyLiving>;

    std::cout << "test_a - forced Living_impl:\n"
              << parse_type_name<test_a>() << '\n';
    std::cout << "test_b:\n"
              << parse_type_name<test_b>() << '\n';
    std::cout << "test_c:\n"
              << parse_type_name<test_c>() << '\n'
              << '\n';

    std::cout << "test_a - base Livingable - forced Living_impl:\n"
              << parse_type_name<test_a2>() << '\n';
    std::cout << "test_b - base Livingable:\n"
              << parse_type_name<test_b2>() << '\n';
    std::cout << "test_c - base Livingable:\n"
              << parse_type_name<test_c2>() << '\n'
              << '\n';
}

TEST(add_two_kind_of_property_to_same_type, base_empty) {
    using type = add_properties_ordered<empty, Damaging, Living, MyDamaging, MyLiving>;

    static_assert(std::same_as<
                  add_properties_ordered<empty, Damaging, MyDamaging>,
                  add_properties_ordered<empty, MyDamaging, Damaging>>);

    using type1 = add_properties_ordered<empty, Damaging, Living>;
    using type2 = add_properties_ordered<type1, MyDamaging, MyLiving>;

    static_assert(not helpers::impl::same_priority<Property<Damaging>, Property<MyDamaging>>::value);
    static_assert(std::same_as<
                  helpers::create_ordered_property_list<Living, MyLiving>,
                  helpers::create_ordered_property_list<MyLiving, Living>>);

    EXPECT_TRUE((std::same_as<type2, type>));

    using typea = add_properties_ordered<empty, MyDamaging, MyLiving>;
    using typeb = add_properties_ordered<typea, Damaging, Living>;

    EXPECT_TRUE((std::same_as<typeb, type>));

    std::cout << "empty -> Damaging, Living     -> MyDamaging, MyLiving" << parse_type_name<type2>() << '\n';
    std::cout << "empty -> MyDamaging, MyLiving -> Damaging, Living" << parse_type_name<typeb>() << '\n';
    std::cout << "empty -> Damaging, Living, MyDamaging, MyLiving" << parse_type_name<type>() << '\n';
}

TEST(add_two_kind_of_property_to_same_type, base_with_health) {
    using type = add_properties_ordered<with_health, Damaging, Living, MyDamaging, MyLiving>;

    static_assert(std::same_as<
                  add_properties_ordered<with_health, Damaging, MyDamaging>,
                  add_properties_ordered<with_health, MyDamaging, Damaging>>);

    using type1 = add_properties_ordered<with_health, Damaging, Living>;
    using type2 = add_properties_ordered<type1, MyDamaging, MyLiving>;

    static_assert(not helpers::impl::same_priority<Property<Damaging>, Property<MyDamaging>>::value);
    static_assert(std::same_as<
                  helpers::create_ordered_property_list<Living, MyLiving>,
                  helpers::create_ordered_property_list<MyLiving, Living>>);

    EXPECT_TRUE((std::same_as<type2, type>));

    using typea = add_properties_ordered<with_health, MyDamaging, MyLiving>;
    using typeb = add_properties_ordered<typea, Damaging, Living>;

    EXPECT_TRUE((std::same_as<typeb, type>));

    std::cout << "with_health -> Damaging, Living     -> MyDamaging, MyLiving" << parse_type_name<type2>() << '\n';
    std::cout << "with_health -> MyDamaging, MyLiving -> Damaging, Living" << parse_type_name<typeb>() << '\n';
    std::cout << "with_health -> Damaging, Living, MyDamaging, MyLiving" << parse_type_name<type>() << '\n';
}

TEST(add_two_kind_of_property_to_same_type, base_builded) {
    using type = add_properties_ordered<with_health, Damaging, MyLiving>;

    static_assert(std::same_as<
                  add_properties_ordered<type, Damaging, MyDamaging, Living_impl>,
                  add_properties_ordered<type, MyDamaging, Damaging, Living_impl>>);

    std::cout << parse_type_name<type>() << '\n';
    std::cout << parse_type_name<add_properties_ordered<type, Damaging, MyDamaging, Living_impl>>() << '\n';
}

auto print = []([[maybe_unused]] std::string_view text, [[maybe_unused]] auto value = empty{}) {
    if constexpr (std::same_as<empty, decltype(value)>) {
        // std::cout << text << '\n';
    } else {
        // std::cout << text << value.value() << "   [" << name<decltype(value)>() << "]\n";
    }
};

auto check = []<typename type>(type& obj, std::string texted_type) {
    print(texted_type, empty{});

    EXPECT_TRUE((detect<member_getType, type, val<0>>::value));
    EXPECT_TRUE((detect<member_getType, type, val<1>>::value));
    EXPECT_TRUE((detect<member_getType, type, val<2>>::value));
    print("memb getType<0>: ", obj.template getType<0>());
    print("memb getType<1>: ", obj.template getType<1>());
    print("memb getType<2>: ", obj.template getType<2>());
    if constexpr ((detect<member_getType, type, val<3>>::value)) {
        print("memb getType<3>: ", obj.template getType<3>());
    } else {
        print("memb getType<3>: unaccessable", empty{});  //? deleted method - base don't have getType
    }

    EXPECT_TRUE((detect<free_getType, type, val<0>>::value));
    EXPECT_TRUE((detect<free_getType, type, val<1>>::value));
    EXPECT_TRUE((detect<free_getType, type, val<2>>::value));
    EXPECT_TRUE((detect<free_getType, type, val<3>>::value));
    EXPECT_FALSE((detect<free_getType, type, val<4>>::value));  //? deleted function - out of range
    print("free getType<0>: ", getType<0>(obj));
    print("free getType<1>: ", getType<1>(obj));
    print("free getType<2>: ", getType<2>(obj));
    print("free getType<3>: ", getType<3>(obj));
    // std::cout << "free2: " << getType<4>(obj).value() << '\n';  //? deleted function - out of range

    EXPECT_TRUE((detect<member_getTypeTaged, type, Health, tag_health>::value));
    EXPECT_TRUE((detect<member_getTypeTaged, type, Damage, tag_damage>::value));
    EXPECT_TRUE((detect<member_getTypeTaged, type, Damage>::value));
    print("memb getTypeTaged<Health, tag_health>: ", obj.template getTypeTaged<Health, tag_health>());
    print("memb getTypeTaged<Damage, tag_damage>: ", obj.template getTypeTaged<Damage, tag_damage>());
    print("memb getTypeTaged<Damage>:             ", obj.template getTypeTaged<Damage>());
    if constexpr ((detect<member_getTypeTaged, type, Health>::value)) {
        print("memb getTypeTaged<Health>:             ", obj.template getTypeTaged<Health>());
    } else {
        print("memb getTypeTaged<Health>:             unaccessable", empty{});  //? deleted method - base don't have getTypeTaged
    }

    EXPECT_TRUE((detect<free_getTypeTaged, type, Health, tag_health>::value));
    EXPECT_TRUE((detect<free_getTypeTaged, type, Damage, tag_damage>::value));
    EXPECT_TRUE((detect<free_getTypeTaged, type, Health>::value));
    EXPECT_TRUE((detect<free_getTypeTaged, type, Damage>::value));
    EXPECT_FALSE((detect<free_getTypeTaged, type, Protection>::value));         //? deleted function - wrong type
    EXPECT_FALSE((detect<free_getTypeTaged, type, Health, tag_wrong>::value));  //? deleted function - wrong tag
    print("free getTypeTaged<Health, tag_health>: ", getTypeTaged<Health, tag_health>(obj));
    print("free getTypeTaged<Damage, tag_damage>: ", getTypeTaged<Damage, tag_damage>(obj));
    print("free getTypeTaged<Damage>            : ", getTypeTaged<Damage>(obj));
    print("free getTypeTaged<Health>            : ", getTypeTaged<Health>(obj));
    // std::cout << "free getTypeTaged<Protection>:         " << getTypeTaged<Protection>(obj).value() << '\n';  //? deleted function - wrong type
    // std::cout << "free getTypeTaged<Health, tag_wrong>:  " << getTypeTaged<Health, tag_wrong>(obj).value() << '\n';  //? deleted function - wrong tag

    print("", empty{});

    EXPECT_TRUE(getTypeTaged<Health>(obj) == base_health);
    EXPECT_TRUE(getTypeTaged<Damage>(obj) == base_damage);
    EXPECT_TRUE((getTypeTaged<Damage, tag_damage>(obj)) == taged_damage);
    EXPECT_TRUE((getTypeTaged<Health, tag_health>(obj)) == taged_health);
};

TEST_F(Access_Fixture_empty, access_by_method_and_free_function) {
    std::cout << parse_type_name<type>() << '\n';

    check(obj_by_list, "by list");
    check(obj_by_create, "by create");
    check(obj_by_creator, "by creator");
}

TEST_F(Access_Fixture_with_health, access_by_method_and_free_function) {
    std::cout << parse_type_name<type>() << '\n';

    check(obj_by_list, "by list");
    check(obj_by_create, "by create");
    check(obj_by_creator, "by creator");
}

TEST_F(Access_Fixture_with_health_and_damage, access_by_method_and_free_function) {
    std::cout << parse_type_name<type>() << '\n';

    check(obj_by_list, "by list");
    check(obj_by_create, "by create");
    check(obj_by_creator, "by creator");
}
