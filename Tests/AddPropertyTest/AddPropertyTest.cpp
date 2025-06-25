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

TEST(AddPropertyTest, add_new_property) {
    using base = empty;
    using type = add_properties_ordered<base, Living>;

    std::cout << parse_type_name<type>() << '\n';

    EXPECT_FALSE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}

TEST(AddPropertyTest, add_property_already_in_base) {
    using base = with_health;
    using type = add_properties_ordered<base, Living>;
    
    std::cout << parse_type_name<type>() << '\n';
    
    EXPECT_TRUE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}
TEST(AddPropertyTest, add_property_taged_already_in_base) {
    using base = with_health;
    using type = add_properties_ordered<base, Living_taged>;
    
    std::cout << parse_type_name<type>() << '\n';
    
    EXPECT_FALSE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}
TEST(AddPropertyTest, add_property_taged_once_already_in_base) {
    using base = with_health;
    using type = add_properties_ordered<base, Living_taged_once>;
    
    std::cout << parse_type_name<type>() << '\n';
    
    EXPECT_TRUE((std::is_same_v<base, type>));
    EXPECT_TRUE(trait<Health>::is_accessable<type>);
}
