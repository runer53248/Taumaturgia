#pragma once
#include "Object/Properties/UserProperty.hpp"
#include "Object/Properties/Properties.hpp"

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

std::ostream& operator<<(std::ostream& stream, const Name& name) {
    return stream << std::string(name);
}
