#include <gtest/gtest.h>
#include <experimental/type_traits>
#include "Introduction/parse_type_name.hpp"
#include "Taumaturgia/Traits/access_features.hpp"
#include "Usage/With.hpp"

// MARK: empty, tag_health, with_health

struct empty {};
struct tag_health {};
struct tag_damage {};
struct tag_wrong {};

static_assert(Property<Living>::value < Property<Damaging>::value);

struct with_health {
    using hold_type = Health;

    Health hp;
};

Health base_health{30};
Health tagged_health{15};

// MARK: properties

template <typename T>
using MyLiving = AdvanceUserProperty<::Health, tag_health>::type<T>;
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

using namespace testing;

class Access_Fixture : public Test {
public:
    Health base_health{30};
    Health tagged_health{15};

    Damage base_damage{10};
    Damage taged_damage{100};

    using base = with_health;
    using type = add_properties_ordered<base, MyLiving, MyDamaging, Damaging>;  //! Damaging ignored

    static_assert(std::same_as<
                  add_properties_ordered<base, MyLiving, MyDamaging, Damaging>,
                  add_properties_ordered<base, MyLiving, MyDamaging>>);

    //! With::Damage ignored
    type obj_by_list = base{Health{base_health}} | (With::MyHealth | With::MyDamage | With::Damage);                                          // set base value
    type obj_by_create = base{Health{base_health}} | With::MyHealth | With::MyDamage | With::Damage | Create;                                 // set base value
    type obj_by_creator = (From::base<base> | With::MyHealth | With::MyDamage /*| With::Damage*/)(tagged_health, taged_damage, base_health);  // set both added and base values

protected:
    void SetUp() override {
        trait<Health>::get(obj_by_list) = tagged_health;  // set added value
        trait<Damage>::get(obj_by_list) = taged_damage;   // set added value

        trait<Health>::get(obj_by_create) = tagged_health;  // set added value
        trait<Damage>::get(obj_by_create) = taged_damage;   // set added value
    }
    void TearDown() override {}
};

// MARK: tests

TEST(add_two_kind_of_property_to_same_type, test) {
    using type = add_properties_ordered<empty, Damaging, Living, MyDamaging, MyLiving>;

    static_assert(std::same_as<
                  add_properties_ordered<empty, Damaging, MyDamaging>,
                  add_properties_ordered<empty, MyDamaging, Damaging>>);

    using type1 = add_properties_ordered<empty, Damaging, Living>;
    using type2 = add_properties_ordered<type1, MyDamaging, MyLiving>;  // ? taged added on untaged

    std::cout << "empty -> Damaging, Living:\n"
              << name<type1>() << '\n'
              << '\n';
    std::cout << "empty -> Damaging, Living -> MyDamaging, MyLiving:\n"
              << name<type2>() << '\n'
              << '\n';
              
    EXPECT_TRUE((std::same_as<type2, type>));

    using typea = add_properties_ordered<empty, MyDamaging, MyLiving>;
    using typeb = add_properties_ordered<typea, Damaging, Living>;  // ! taged block untaged

    std::cout << "empty -> MyDamaging, MyLiving:\n"
              << name<typea>() << '\n'
              << '\n';
    std::cout << "empty -> MyDamaging, MyLiving -> Damaging, Living:\n"
              << name<typeb>() << '\n'
              << '\n';

    EXPECT_TRUE((std::same_as<typeb, type>));

    std::cout << "empty -> Damaging, Living     -> MyDamaging, MyLiving" << parse_type_name<type2>() << '\n';
    std::cout << "empty -> MyDamaging, MyLiving -> Damaging, Living" << parse_type_name<typeb>() << '\n';
    std::cout << "empty -> Damaging, Living, MyDamaging, MyLiving" << parse_type_name<type>() << '\n';
}

TEST_F(Access_Fixture, access_by_method_and_free_function) {
    std::cout << parse_type_name<type>() << '\n';

    auto check = [&](type& obj, std::string texted_type) {
        std::cout << texted_type << '\n';

        EXPECT_TRUE((detect<member_getType, type, val<0>>::value));
        EXPECT_TRUE((detect<member_getType, type, val<1>>::value));
        EXPECT_FALSE((detect<member_getType, type, val<2>>::value));  //? deleted method - base don't have getType
        std::cout << "memb getType<0>: " << obj.getType<0>().value() << '\n';
        std::cout << "memb getType<1>: " << obj.getType<1>().value() << '\n';
        std::cout << "memb getType<2>: unaccessable \n";
        // std::cout << obj.getType<2>().value() << '\n';  //? deleted method - base don't have getType

        EXPECT_TRUE((detect<free_getType, type, val<0>>::value));
        EXPECT_TRUE((detect<free_getType, type, val<1>>::value));
        EXPECT_TRUE((detect<free_getType, type, val<2>>::value));
        EXPECT_FALSE((detect<free_getType, type, val<3>>::value));  //? deleted function - out of range
        std::cout << "free getType<0>: " << getType<0>(obj).value() << '\n';
        std::cout << "free getType<1>: " << getType<1>(obj).value() << '\n';
        std::cout << "free getType<2>: " << getType<2>(obj).value() << '\n';
        // std::cout << "free2: " << getType<3>(obj).value() << '\n';  //? deleted function - out of range

        EXPECT_TRUE((detect<member_getTypeTaged, type, Health, tag_health>::value));
        EXPECT_TRUE((detect<member_getTypeTaged, type, Damage, tag_damage>::value));
        EXPECT_FALSE((detect<member_getTypeTaged, type, Health>::value));  //? deleted method - base don't have getTypeTaged
        std::cout << "memb getTypeTaged<Health, tag_health>: " << obj.getTypeTaged<Health, tag_health>().value() << '\n';
        std::cout << "memb getTypeTaged<Damage, tag_damage>: " << obj.getTypeTaged<Damage, tag_damage>().value() << '\n';
        std::cout << "memb getTypeTaged<Health>:             unaccessable \n";
        // std::cout << obj.getTypeTaged<Health>().value() << '\n';  //? deleted method - base don't have getTypeTaged

        EXPECT_TRUE((detect<free_getTypeTaged, type, Health, tag_health>::value));
        EXPECT_TRUE((detect<free_getTypeTaged, type, Health>::value));
        EXPECT_TRUE((detect<free_getTypeTaged, type, Damage, tag_damage>::value));
        EXPECT_FALSE((detect<free_getTypeTaged, type, Damage>::value));             //? deleted function - wrong type
        EXPECT_FALSE((detect<free_getTypeTaged, type, Health, tag_wrong>::value));  //? deleted function - wrong tag
        std::cout << "free getTypeTaged<Health, tag_health>: " << getTypeTaged<Health, tag_health>(obj).value() << '\n';
        std::cout << "free getTypeTaged<Damage, tag_damage>: " << getTypeTaged<Damage, tag_damage>(obj).value() << '\n';
        std::cout << "free getTypeTaged<Health>            : " << getTypeTaged<Health>(obj).value() << '\n';
        // std::cout << "free getTypeTaged<Damage>:             " << getTypeTaged<Damage>(obj).value() << '\n';  //? deleted function - wrong type
        // std::cout << "free getTypeTaged<Health, tag_wrong>:  " << getTypeTaged<Health, tag_wrong>(obj).value() << '\n';  //? deleted function - wrong tag

        std::cout << '\n';

        EXPECT_TRUE(getType<1>(obj) == taged_damage);
        EXPECT_TRUE(getType<2>(obj) == base_health);
        EXPECT_TRUE(getType<0>(obj) == tagged_health);

        EXPECT_TRUE(getTypeTaged<Health>(obj) == base_health);
        EXPECT_TRUE((getTypeTaged<Health, tag_health>(obj)) == tagged_health);
    };

    check(obj_by_list, "by list");
    check(obj_by_create, "by create");
    check(obj_by_creator, "by creator");
    std::cout << '\n';
}
