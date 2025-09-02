#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"

struct MyType {};

using type_1 = float;
using type_2 = int;
using type_3 = bool;

using TestType = add_properties_ordered<
    MyType,
    //
    UserPropertyAdapter<type_1>::once,  // not on order_list - last on c-tor arguments list
    UserPropertyAdapter<type_2>::once,    // not on order_list - always apply to MyType as most inner (before Naming !!!)
    UserPropertyAdapter<type_3>::once,
    // below are in order_list order
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming>;

// TestType arguments order
//
// TestType(
//     Naming, // c-tors move Naming property in front (but its added to MyType as last of ordered properties)
//     Living,
//     Wearing,
//     Damaging,
//     Protecting,
//     Healing,
//     Restoring,
//     float, // properties not in order_list are unordered (order in add_properties is used)
//     int,
//     bool)

// Living < Wearing < Damaging < Protecting < Healing < Restoring < Naming < UserPropertyAdapter<float>::type
// UserPropertyAdapter<float>::type == UserPropertyAdapter<int>::type == UserPropertyAdapter<bool>::type
static_assert(Property_ordered<Living>::value < Property_ordered<Wearing>::value);
static_assert(Property_ordered<Wearing>::value < Property_ordered<Damaging>::value);
static_assert(Property_ordered<Damaging>::value < Property_ordered<Protecting>::value);
static_assert(Property_ordered<Protecting>::value < Property_ordered<Healing>::value);
static_assert(Property_ordered<Healing>::value < Property_ordered<Restoring>::value);
static_assert(Property_ordered<Restoring>::value < Property_ordered<Naming>::value);
static_assert(Property_ordered<Naming>::value < Property_ordered<UserPropertyAdapter<type_1>::once>::value);
static_assert(Property_ordered<UserPropertyAdapter<type_1>::once>::value == Property_ordered<UserPropertyAdapter<type_2>::once>::value);
static_assert(Property_ordered<UserPropertyAdapter<type_1>::once>::value == Property_ordered<UserPropertyAdapter<type_3>::once>::value);

using helpers::is_same_priority;

static_assert(not is_same_priority<
              Property_ordered<UserPropertyAdapter<type_1>::once>,
              Property_ordered<UserPropertyAdapter<type_2>::once>>);
static_assert(not is_same_priority<
              Property_ordered<UserPropertyAdapter<type_1>::once>,
              Property_ordered<UserPropertyAdapter<type_3>::once>>);
static_assert(not is_same_priority<
              Property_ordered<UserPropertyAdapter<type_2>::once>,
              Property_ordered<UserPropertyAdapter<type_3>::once>>);

auto& operator<<(std::ostream& stream, const Name& name) {
    return stream << std::string(name);
}
