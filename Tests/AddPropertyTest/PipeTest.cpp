#include <gtest/gtest.h>

#include "Introduction/parse_type_name.hpp"

#include "Usage/With.hpp"

struct empty {};

struct with_health {
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

TEST(PipeTest, add_new_property) {
    using base = empty;
    using type = decltype(base{} | With::Health | Create);
    using type2 = decltype(From::base<base> | With::Health)::result_type;

    std::cout << parse_type_name<type>() << '\n';
    std::cout << parse_type_name<type2>() << '\n';

    EXPECT_FALSE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}

TEST(PipeTest, add_property_already_in_base) {
    using base = with_health;
    using type = decltype(base{} | With::Health | Create);
    using type2 = decltype(From::base<base> | With::Health)::result_type;

    std::cout << parse_type_name<type>() << '\n';
    std::cout << parse_type_name<type2>() << '\n';

    EXPECT_TRUE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}
TEST(PipeTest, add_property_taged_already_in_base) {
    using base = with_health;
    using type = decltype(base{} | With::MyHealth | Create);
    using type2 = decltype(From::base<base> | With::MyHealth)::result_type;

    std::cout << parse_type_name<type>()
              << '\n'
              << parse_type_name<type2>()
              << '\n';

    EXPECT_FALSE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}
TEST(PipeTest, add_property_taged_once_already_in_base) {
    using base = with_health;
    base b{};
    using type0 = decltype(b | With::MyHealth_once | Create);
    using type1 = decltype(base{} | With::MyHealth_once | Create);
    using type2 = decltype(From::base<base> | With::MyHealth_once)::result_type;

    std::cout << parse_type_name<type0>()
              << '\n'
              << parse_type_name<type1>()
              << '\n'
              << parse_type_name<type2>()
              << '\n';

    // EXPECT_TRUE((std::is_same_v<base, type0>));
    // EXPECT_TRUE((std::is_same_v<base, type1>));
    EXPECT_TRUE((std::is_same_v<base, type2>));
    EXPECT_TRUE(trait<Health>::is_accessable<type1>);
}
