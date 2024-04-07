#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/improved_types.hpp"

using helpers::is_property_improvement;
using helpers::same_priority;

int main() {
    static_assert(Property<Damaging>::value == Property<Damaging_impl>::value);
    static_assert(same_priority<Property<Damaging>, Property<Damaging_impl>>);

    // improvements of build-in properties
    static_assert(Property<Damaging>::value == Property<DamagingImproved>::value);
    static_assert(same_priority<Property<Damaging>, Property<DamagingImproved>>);
    static_assert(same_priority<Property<Damaging_impl>, Property<DamagingImproved>>);
    std::cout << "build-in properties can be improved" << '\n';
    std::cout << "Damaging priority = " << Property<Damaging>::value << " | improved = " << is_property_improvement<Damaging> << '\n';
    std::cout << "Damaging_impl priority = " << Property<Damaging_impl>::value << " | improved = " << is_property_improvement<Damaging_impl> << '\n';
    std::cout << "DamagingImproved priority = " << Property<DamagingImproved>::value << " | improved = " << is_property_improvement<DamagingImproved> << '\n';
    std::cout << "DamagingImproved_ priority = " << Property<DamagingImproved_>::value << " | improved = " << is_property_improvement<DamagingImproved_> << '\n'
              << '\n';

    // improvements of user properties
    static_assert(Property<UserProtectingImproved>::value == Property<UserProtecting>::value);
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtecting>>);            // ? same_priority value
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtectingImproved>>);            // ? same_priority value
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtectingImproved>>);    // ? same_priority value
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtectingImproved_2>>);  // ? same_priority value
    std::cout << "user properties can be improved" << '\n';
    std::cout << "UserProtecting priority = " << Property<UserProtecting>::value << " | improved = " << is_property_improvement<UserProtecting> << '\n';
    std::cout << "UserProtectingImproved priority = " << Property<UserProtectingImproved>::value << " | improved = " << is_property_improvement<UserProtectingImproved> << '\n';
    std::cout << "UserProtectingImproved_ priority = " << Property<UserProtectingImproved_>::value << " | improved = " << is_property_improvement<UserProtectingImproved_> << '\n';
    std::cout << "UserProtectingImproved_2 priority = " << Property<UserProtectingImproved_2>::value << " | improved = " << is_property_improvement<UserProtectingImproved_2> << '\n';
    std::cout << "UserProtectingImproved_2_ priority = " << Property<UserProtectingImproved_2_>::value << " | improved = " << is_property_improvement<UserProtectingImproved_2_> << '\n'
              << '\n';

    // UserProperty may have same priority value but are not considered same by same_priority struct
#ifndef NO_PREMADE_PROPERTIES
    static_assert(Property<UserProtecting>::value == Property<UserDamaging>::value);  // same priority value
#else
    static_assert(Property<UserProtecting>::value != Property<UserDamaging>::value);  // not same priority value
#endif
    static_assert(Property<UserProtecting>::value == Property<UserProtecting_2>::value);  // same priority value
    static_assert(Property<UserProtecting>::value == Property<UserProtecting>::value);    // same priority value
    static_assert(not same_priority<Property<UserProtecting>, Property<UserDamaging>>);   // not same_priority value - different types
#ifdef USER_PROPERTY_SELF_AWARE
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtecting_2>>);  // same_priority value - self type awarness
#else
#ifndef NO_PREMADE_PROPERTIES
    static_assert(not same_priority<Property<UserProtecting>, Property<UserProtecting_2>>);  // not same_priority value - different type even if similiar
#else
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtecting_2>>);  // same_priority value
#endif
#endif
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtecting>>);  // same type have same_priority value

    struct Type {
    public:
        Damage dmg;
        Damage dmgs;

        auto& getType() {
            return dmg;
        }
    };
    std::cout << "build-in property may shadow members" << '\n'
              << "and methods of type that pass validation concept for property" << '\n';
    std::cout << name<Damaging<Type>>() << '\n';
    std::cout << name<Damaging_impl<Type>>() << '\n'
              << '\n';
    // [[maybe_unused]] auto a = Damaging_impl<Type>{}.dmg; // public dmg is shadowed by private one from Damaging_
    std::cout << "Damaging_impl<Type>{}.dmg is shadowed \n";

    [[maybe_unused]] auto b = Damaging_impl<Type>{}.dmgs;
    std::cout << "Damaging_impl<Type>{}.dmgs = " << b << '\n';
    
#ifndef NO_PREMADE_PROPERTIES
    [[maybe_unused]] auto c = Damaging_impl<Type>{}.getType();  // Type::getType method call
    std::cout << "Damaging_impl<Type>{}.getType() = " << c << '\n';
#else
    // [[maybe_unused]] auto c = Damaging_impl<Type>{}.getType(); // ! public getType is shadowed by protected one from UserProperty
    std::cout << "Damaging_impl<Type>{}.getType() is shadowed " << '\n';
#endif

    std::cout << "custom property may shadow members and methods of type that pass validation concept for property" << '\n';
    [[maybe_unused]] auto d = UserDamaging<Type>{}.dmg;
    [[maybe_unused]] auto e = UserDamaging<Type>{}.dmgs;
    // [[maybe_unused]] auto f = UserDamaging<Type>{}.getType(); // ! public getType is shadowed by protected one from UserProperty
    std::cout << "UserProperty<Damage, Type>{}.dmg = " << d << '\n';
    std::cout << "UserProperty<Damage, Type>{}.dmgs = " << e << '\n';
    std::cout << "UserProperty<Damage, Type>{}.getType() shadowed \n";
    std::cout << name<UserDamaging<Type>>() << '\n'
              << '\n';
}
