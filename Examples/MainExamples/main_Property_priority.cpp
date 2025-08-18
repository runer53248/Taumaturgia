#include <iostream>
#include "Examples/Checks.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/Properties.hpp"

template <typename T>
struct PlainProperty : public T {
    using property_data = PropertyData<PlainProperty, T>;
    using hold_type = void;
};

// order in order_list
// | Living
// | Wearing
// | Damaging
// | Protecting
// | Healing
// | Restoring
// V Naming
//
//... any not in order_list same last position (no ordering them but put close to type)

//  order of apply to type
//    <      -       -         -         -       -       -     ...
// Living<Wearing<Damaging<Protecting<Healing<Restoring<Naming<...<TYPE>>>>>>>>

int main() {
    std::cout << "B. 'Property<...>::value' priority examples:" << '\n'
              << '\n';

    std::cout << "1) print priority of unknown properties" << '\n';
    std::cout << Property<PlainProperty>::value << " - PlainProperty priority" << '\n';
    std::cout << '\n';

    std::cout << "2) print priority of known from order_list properties" << '\n';
    std::cout << Property<Naming>::value << " - Naming priority" << '\n';
    std::cout << Property<Living>::value << " - Living priority" << '\n';
    std::cout << Property<Wearing>::value << " - Wearing priority" << '\n';
    std::cout << Property<Damaging>::value << " - Damaging priority" << '\n';
    std::cout << Property<Protecting>::value << " - Protecting priority" << '\n';
    std::cout << Property<Healing>::value << " - Healing priority" << '\n';
    std::cout << Property<Restoring>::value << " - Restoring priority" << '\n';
    std::cout << '\n';

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
