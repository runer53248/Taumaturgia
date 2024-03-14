#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"
#include "Examples/property_C.hpp"

int main() {
    std::cout << "B. 'Property<...>::value' priority examples:" << '\n'
              << '\n';

    std::cout << "1) print priority of unknown properties" << '\n';
    std::cout << Property<A>::value << " - A priority" << '\n';
    std::cout << Property<B>::value << " - B priority" << '\n';
    std::cout << Property<C>::value << " - C priority" << '\n';
    std::cout << '\n';

    std::cout << "2) print priority of known properties" << '\n';
    std::cout << Property<Naming>::value << " - Naming priority" << '\n';
    std::cout << Property<Living>::value << " - Living priority" << '\n';
    std::cout << Property<Wearing>::value << " - Wearing priority" << '\n';
    std::cout << Property<Damaging>::value << " - Damaging priority" << '\n';
    std::cout << Property<Protecting>::value << " - Protecting priority" << '\n';
    std::cout << Property<Healing>::value << " - Healing priority" << '\n';
    std::cout << Property<Restoring>::value << " - Restoring priority" << '\n';
    std::cout << '\n';

    return 0;
}
