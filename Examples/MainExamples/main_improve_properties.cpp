#include "../demangle_type_name.hpp"
#include "../improved_types.hpp"
#include "Examples/preety_print.hpp"

int main() {
    static_assert(Property<Damaging>::value == Property<impl::Damaging_>::value);
    static_assert(same_priority<Property<Damaging>, Property<impl::Damaging_>>::value);

    // improvements of build-in properties
    static_assert(Property<Damaging>::value == Property<DamagingImproved>::value);
    static_assert(same_priority<Property<Damaging>, Property<DamagingImproved>>::value);
    static_assert(same_priority<Property<impl::Damaging_>, Property<DamagingImproved>>::value);
    std::cout << "build-in properties can be improved" << '\n';
    std::cout << "Damaging priority = " << Property<Damaging>::value << " | improved = " << property_improvement<Damaging> << '\n';
    std::cout << "impl::Damaging_ priority = " << Property<impl::Damaging_>::value << " | improved = " << property_improvement<impl::Damaging_> << '\n';
    std::cout << "DamagingImproved priority = " << Property<DamagingImproved>::value << " | improved = " << property_improvement<DamagingImproved> << '\n';
    std::cout << "DamagingImproved_ priority = " << Property<DamagingImproved_>::value << " | improved = " << property_improvement<DamagingImproved_> << '\n'
              << '\n';

    // improvements of user properties
    static_assert(Property<UserProtectingImproved>::value == Property<UserProtecting>::value);
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtecting>>::value);            // ? same_priority value
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtectingImproved>>::value);            // ? same_priority value
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtectingImproved>>::value);    // ? same_priority value
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtectingImproved_2>>::value);  // ? same_priority value
    std::cout << "user properties can be improved" << '\n';
    std::cout << "UserProtecting priority = " << Property<UserProtecting>::value << " | improved = " << property_improvement<UserProtecting> << '\n';
    std::cout << "UserProtectingImproved priority = " << Property<UserProtectingImproved>::value << " | improved = " << property_improvement<UserProtectingImproved> << '\n';
    std::cout << "UserProtectingImproved_ priority = " << Property<UserProtectingImproved_>::value << " | improved = " << property_improvement<UserProtectingImproved_> << '\n';
    std::cout << "UserProtectingImproved_2 priority = " << Property<UserProtectingImproved_2>::value << " | improved = " << property_improvement<UserProtectingImproved_2> << '\n';
    std::cout << "UserProtectingImproved_2_ priority = " << Property<UserProtectingImproved_2_>::value << " | improved = " << property_improvement<UserProtectingImproved_2_> << '\n'
              << '\n';

    // UserProperty may have same priority value but are not considered same by same_priority struct
    static_assert(Property<UserProtecting>::value == Property<UserDamaging>::value);                // same priority value
    static_assert(Property<UserProtecting>::value == Property<UserProtecting_2>::value);            // same priority value
    static_assert(Property<UserProtecting>::value == Property<UserProtecting>::value);              // same priority value
    static_assert(not same_priority<Property<UserProtecting>, Property<UserDamaging>>::value);      // not same_priority value - different types
    static_assert(not same_priority<Property<UserProtecting>, Property<UserProtecting_2>>::value);  // not same_priority value - different type even if similiar
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtecting>>::value);        // same type have same_priority value

    struct Type {
    public:
        Damage dmgs;
        Damage dmg;

        auto& getType() {
            return dmg;
        }
    };
    std::cout << "build-in property may shadow members and methods of type that pass validation concept for property" << '\n';
    std::cout << name<Damaging<Type>>() << '\n';
    std::cout << name<impl::Damaging_<Type>>() << '\n'
              << '\n';
    // [[maybe_unused]] auto a = impl::Damaging_<Type>{}.dmg; // public dmg is shadowed by private one from Damaging_
    [[maybe_unused]] auto b = impl::Damaging_<Type>{}.dmgs;
    [[maybe_unused]] auto c = impl::Damaging_<Type>{}.getType();

    std::cout << "custom property may shadow members and methods of type that pass validation concept for property" << '\n';
    [[maybe_unused]] auto d = UserDamaging<Type>{}.dmg;
    [[maybe_unused]] auto e = UserDamaging<Type>{}.dmgs;
    // [[maybe_unused]] auto f = UserDamaging<Type>{}.getType(); // ! public getType is shadowed by protected one from UserProperty
    std::cout << name<UserDamaging<Type>>() << '\n'
              << '\n';
}
