#include <gtest/gtest.h>
#include <experimental/type_traits>
#include <print>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Type_without_protection {};

struct Type_with_private_protection {
private:
    // BUG: as private may not be set in unordered c-tor
    Protection protection{};  //! as private may not be set in unordered c-tor

public:
    template <size_t N>
        requires(N == 0)
    decltype(auto) getType(this auto& self) {
        return (self.protection);
    }
    template <size_t N>
    decltype(auto) getType(this auto& self) = delete;

    template <std::same_as<Protection> T, size_t S = 0>
        requires(S == 0)
    decltype(auto) getType(this auto& self) {
        return (self.protection);
    }
    template <typename T, size_t S = 0>
    decltype(auto) getType(this auto& self) = delete;
};

struct Type_with_public_protection {
public:
    Protection protection{};

    template <size_t N>
        requires(N == 0)
    decltype(auto) getType(this auto& self) {
        return (self.protection);
    }
    template <size_t N>
    decltype(auto) getType(this auto& self) = delete;

    template <std::same_as<Protection> T, size_t S = 0>
        requires(S == 0)
    decltype(auto) getType(this auto& self) {
        return (self.protection);
    }
    template <typename T, size_t S = 0>
    decltype(auto) getType(this auto& self) = delete;
};

using x_tag = Tags<struct x>;

auto property_value_tested = Protection{18, BodyLocation::Arms};
auto property_value_tested_2 = Protection{20, BodyLocation::Legs};

template <>
struct UserDefaultValue<Protection, x_tag> {
    static constexpr auto value = [] { return Protection{30, BodyLocation::Head}; };
};

namespace With {
constexpr auto Protection_x = user_property<::Protection, x_tag>;
}  // namespace With

namespace WithUnordered {
constexpr auto Protection_x = user_property<::Protection, x_tag>;
}  // namespace WithUnordered

// MARK: tests

TEST(test_initialization_of_single_property, Type_without_protection) {
    auto type = (                            //
        From::base<Type_without_protection>  //
        | With::Protection_x                 //
        )(                                   //
        unordered,
        property_value_tested);

    std::println("getType<0> = {}", type.getType<0>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, x_tag>(type) == property_value_tested));
}

TEST(test_initialization_of_property_reverse_order, Type_without_protection) {
    auto type = (                            //
        From::base<Type_without_protection>  //
        | WithUnordered::Protection_x        //
        | WithUnordered::Protection          //
        )(                                   //
        unordered,
        property_value_tested);

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
}

TEST(test_initialization_of_property, Type_without_protection) {
    auto type = (                            //
        From::base<Type_without_protection>  //
        | With::Protection                   //
        | With::Protection_x                 //
        )(                                   //
        unordered,
        property_value_tested);

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
}

TEST(test_initialization_of_property, Type_with_private_protection) {
    auto type = (                                 //
        From::base<Type_with_private_protection>  //
        | With::Protection                        //
        | With::Protection_x                      //
        )(                                        //
        unordered,
        property_value_tested);

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
}

TEST(test_initialization_of_property, Type_with_public_protection) {
    auto type = (                                //
        From::base<Type_with_public_protection>  //
        | With::Protection                       //
        | With::Protection_x                     //
        )(                                       //
        unordered,
        property_value_tested);

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
}

TEST(test_initialization_of_both_properties, Type_with_private_protection_2) {
    auto type = (                                 //
        From::base<Type_with_private_protection>  //
        | With::Protection                        //
        | With::Protection_x                      //
        )(                                        //
        unordered,
        forTags<>(property_value_tested),
        forTags<x_tag>(property_value_tested_2));

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
    EXPECT_TRUE((getTypeTaged<Protection, x_tag>(type) == property_value_tested_2));
}

TEST(test_initialization_of_both_properties, Type_with_public_protection_2) {
    auto type = (                                //
        From::base<Type_with_public_protection>  //
        | With::Protection                       //
        | With::Protection_x                     //
        )(                                       //
        unordered,
        forTags<>(property_value_tested),
        forTags<x_tag>(property_value_tested_2));

    std::println("getType<0> = {}", type.getType<0>());
    std::println("getType<1> = {}", type.getType<1>());

    println("{}", parse_type_name<decltype(type)>());

    EXPECT_TRUE((getTypeTaged<Protection, no_tag>(type) == property_value_tested));
    EXPECT_TRUE((getTypeTaged<Protection, x_tag>(type) == property_value_tested_2));
}
