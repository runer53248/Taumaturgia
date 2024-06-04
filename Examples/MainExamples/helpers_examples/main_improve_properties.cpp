#include "Examples/demangle_type_name.hpp"
#include "Examples/improved_types.hpp"

#include "Examples/PreetyPrint/preety_print.hpp"

using helpers::is_property_improvement;
using helpers::is_same_priority;

int main() {
    // improvements of build-in properties
    static_assert(Property<Damaging>::value == Property<DamagingImproved>::value);
    static_assert(is_same_priority<Property<Damaging>, Property<DamagingImproved>>);
    static_assert(is_same_priority<Property<Damaging_impl>, Property<DamagingImproved>>);

    auto printPriority = []<template <typename...> typename T>(std::string const& text) {
        std::cout << text << '\n';
        std::cout << " priority = " << Property<T>::value << " | improved = " << is_property_improvement<T> << '\n';
    };

    std::cout << "build-in properties can be improved" << '\n';
    printPriority.operator()<Damaging>("Damaging");
    printPriority.operator()<Damaging_impl>("Damaging_impl");
    printPriority.operator()<DamagingImproved>("DamagingImproved");
    std::cout << '\n';

    // improvements of user properties
    static_assert(Property<Protecting>::value == Property<UserProtectingImproved>::value);
    static_assert(is_same_priority<Property<Protecting>, Property<UserProtectingImproved>>);
    static_assert(is_same_priority<Property<Protecting_impl>, Property<UserProtectingImproved>>);
    static_assert(is_same_priority<Property<Protecting>, Property<UserProtectingImproved_2>>);
    static_assert(is_same_priority<Property<Protecting_impl>, Property<UserProtectingImproved_2>>);

    std::cout << "user properties can be improved" << '\n';
    printPriority.operator()<Protecting>("Protecting");
    printPriority.operator()<Protecting_impl>("Protecting_impl");
    printPriority.operator()<UserProtectingImproved>("UserProtectingImproved");
    printPriority.operator()<UserProtectingImproved_2>("UserProtectingImproved_2");
    std::cout << '\n';

    // UserProperty may have same priority value but are not considered same by same_priority struct
    static_assert(Property<Protecting_impl>::value != Property<Damaging_impl>::value);  // not same priority value

    static_assert(Property<Protecting_impl>::value == Property<Protecting>::value);  // same priority value
    static_assert(not is_same_priority<
                  Property<Protecting_impl>,
                  Property<Damaging_impl>>);  // not same_priority value - different types
    static_assert(is_same_priority<
                  Property<Protecting>,
                  Property<Protecting_impl>>);  // same type have same_priority value

    struct Type {
    public:
        Damage dmg{10, DamageType::Divine};
        Damage dmgs{20, DamageType::Magical};

        auto& getType() {
            return dmg;
        }
    };
    std::cout << "build-in property may shadow members" << '\n'
              << "and methods of type that pass validation concept for property" << '\n';
    std::cout << name<Damaging<Type>>() << '\n';
    std::cout << name<Damaging_impl<Type>>() << '\n'
              << '\n';
    // [[maybe_unused]] auto dmg_a = Damaging_impl<Type>{}.dmg; // public dmg is shadowed by private one from Damaging_
    std::cout << "Damaging_impl<Type>{}.dmg is shadowed \n";

    auto dmg_b = Damaging_impl<Type>{}.dmgs;
    std::cout << "Damaging_impl<Type>{}.dmgs = " << dmg_b << '\n';

#ifdef NO_PREMADE_PROPERTIES
    // [[maybe_unused]] auto dmg_c = Damaging_impl<Type>{}.getType(); // ! public getType is shadowed by protected one from UserProperty
    std::cout << "Damaging_impl<Type>{}.getType() is shadowed\n";
#else
    [[maybe_unused]] auto dmg_c = Damaging_impl<Type>{}.getType();  // Type::getType method call
    std::cout << "Damaging_impl<Type>{}.getType() = " << dmg_c << '\n';
#endif

    std::cout << "custom property may shadow members and methods\n of type that pass validation concept for property\n";
    auto dmg_d = Damaging_impl<Type>{}.dmg;
    auto dmg_e = Damaging_impl<Type>{}.dmgs;
    // [[maybe_unused]] auto dmg_f = Damaging_impl<Type>{}.getType(); // ! public getType is shadowed by protected one from UserProperty
    std::cout << "Damaging_impl<Type>{}.dmg = " << dmg_d << '\n';
    std::cout << "Damaging_impl<Type>{}.dmgs = " << dmg_e << '\n';
    std::cout << "Damaging_impl<Type>{}.getType() shadowed \n";
    std::cout << name<Damaging_impl<Type>>() << '\n'
              << '\n';
}
