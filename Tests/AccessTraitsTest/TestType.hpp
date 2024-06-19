#pragma once
#include "Usage/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct MyType {};

using type_1 = float;
using type_2 = int;
using type_3 = bool;

using TestType = add_properties<
    MyType,
    //
    UserPropertyAdapter<type_1>::type,  // not on order_list - last on c-tor arguments list
    UserPropertyAdapter<type_2>::type,    // not on order_list - always apply to MyType as most inner (before Naming !!!)
    UserPropertyAdapter<type_3>::type,
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
static_assert(Property<Living>::value < Property<Wearing>::value);
static_assert(Property<Wearing>::value < Property<Damaging>::value);
static_assert(Property<Damaging>::value < Property<Protecting>::value);
static_assert(Property<Protecting>::value < Property<Healing>::value);
static_assert(Property<Healing>::value < Property<Restoring>::value);
static_assert(Property<Restoring>::value < Property<Naming>::value);
static_assert(Property<Naming>::value < Property<UserPropertyAdapter<type_1>::type>::value);
static_assert(Property<UserPropertyAdapter<type_1>::type>::value == Property<UserPropertyAdapter<type_2>::type>::value);
static_assert(Property<UserPropertyAdapter<type_1>::type>::value == Property<UserPropertyAdapter<type_3>::type>::value);

using helpers::is_same_priority;

static_assert(not is_same_priority<
              Property<UserPropertyAdapter<type_1>::type>,
              Property<UserPropertyAdapter<type_2>::type>>);
static_assert(not is_same_priority<
              Property<UserPropertyAdapter<type_1>::type>,
              Property<UserPropertyAdapter<type_3>::type>>);
static_assert(not is_same_priority<
              Property<UserPropertyAdapter<type_2>::type>,
              Property<UserPropertyAdapter<type_3>::type>>);

auto& operator<<(std::ostream& stream, const Name& name) {
    return stream << std::string(name);
}
