#include <gtest/gtest.h>

#include "Introduction/parse_type_name.hpp"

#include "Usage/With.hpp"

struct empty {};

struct with_health {
    using hold_type = Health;
    Health hp;
};

struct tag_health {};

template <typename T>
using Living_taged = AdvanceUserProperty<Health, struct tag_health>::type<T>;

template <typename T>
using Living_taged_once = AdvanceUserProperty<Health, struct tag_health>::order<T>;

namespace With {
[[maybe_unused]] constexpr auto MyHealth = user_property<::Health, struct tag_health>;
[[maybe_unused]] constexpr auto MyHealth_once = user_property_once<::Health, struct tag_health>;
}  // namespace With

static_assert(std::same_as<
              Property<Living_taged>::property_data,
              decltype(With::MyHealth)::property_data>);

static_assert(std::same_as<
              Property<Living_taged_once>::property_data,
              decltype(With::MyHealth_once)::property_data>);

TEST(AddPropertyTest, new_property) {
    using base = empty;
    using type1 = add_properties_ordered<base, Living>;
    using type2 = decltype(base{} | With::Health | Create);
    using type3 = decltype(From::base<base> | With::Health)::result_type;

    static_assert(std::same_as<type1, type2>);
    static_assert(std::same_as<type1, type3>);

    std::cout << parse_type_name<type1>() << '\n';

    EXPECT_FALSE((std::is_same_v<base, type1>));

    EXPECT_TRUE(trait<Health>::is_accessable<type1>);
}

TEST(AddPropertyTest, property_already_in_base) {
    using base = with_health;
    using type1 = add_properties_ordered<base, Living>;
    using type2 = decltype(base{} | With::Health | Create);
    using type3 = decltype(From::base<base> | With::Health)::result_type;
    using type4 = decltype(base{} | list(With::Health));

    static_assert(std::same_as<type1, type2>);
    static_assert(std::same_as<type1, type3>);
    static_assert(std::same_as<type1, type4>);

    std::cout << parse_type_name<type1>() << '\n';

    EXPECT_TRUE((std::is_same_v<base, type1>));

    EXPECT_TRUE(trait<Health>::is_accessable<type1>);
}

TEST(AddPropertyTest, property_taged_already_in_base) {
    using base = with_health;
    using type1 = add_properties_ordered<base, Living_taged>;
    using type2 = decltype(base{} | With::MyHealth | Create);
    using type3 = decltype(From::base<base> | With::MyHealth)::result_type;
    using type4 = decltype(base{} | list(With::MyHealth));

    static_assert(std::same_as<type1, type2>);
    static_assert(std::same_as<type1, type3>);
    static_assert(std::same_as<type1, type4>);

    std::cout << parse_type_name<type1>() << '\n';

    EXPECT_FALSE((std::is_same_v<base, type1>));

    EXPECT_TRUE(trait<Health>::is_accessable<type1>);
}

TEST(AddPropertyTest, property_taged_once_already_in_base) {
    using base = with_health;

    using type1 = add_properties_ordered<base, Living_taged_once>;
    using type2 = decltype(base{} | With::MyHealth_once | Create);
    base b{};
    using type2a = decltype(b | With::MyHealth_once | Create);
    using type3 = decltype(From::base<base> | With::MyHealth_once)::result_type;

    static_assert(std::same_as<type1, type2>);
    static_assert(std::same_as<type1, type2a>);
    static_assert(std::same_as<type1, type3>);

    std::cout << parse_type_name<type1>() << '\n';
    
    EXPECT_TRUE(trait<Health>::is_accessable<type1>);
}

TEST(AddPropertyTest, property_and_property_taged_access) {
    using base = with_health;

    auto value_base = Health{30};
    auto value_taged = Health{15};

    auto type1 = add_properties_ordered<base, Living_taged>{value_taged, value_base};
    auto type2 = (From::base<base> | With::MyHealth)(value_taged, value_base);
    auto type3 = base{value_base} | With::MyHealth | Create;
    auto type4 = base{value_base} | list(With::MyHealth);

    type3.getTaged<tag_health>() = value_taged;
    type4.getTaged<tag_health>() = value_taged;

    auto v1 = trait<Health>::get(type1);
    auto v2 = trait<Health>::get(type2);
    auto v3 = trait<Health>::get(type3);
    auto v4 = trait<Health>::get(type4);

    std::cout << v1.value() << '\n';
    std::cout << v2.value() << '\n';
    std::cout << v3.value() << '\n';
    std::cout << v4.value() << '\n';

    std::cout << parse_type_name<decltype(type1)>() << '\n';
    std::cout << parse_type_name<decltype(type2)>() << '\n';
    std::cout << parse_type_name<decltype(type3)>() << '\n';
    std::cout << parse_type_name<decltype(type4)>() << '\n';
}
