#include "Examples/preety_print.hpp"
#include "../basic_strategies.hpp"
#include "../demangle_type_name.hpp"
#include "../is_base_of_template.hpp"
#include "../property_A.hpp"
#include "../property_B.hpp"

int main() {
    std::cout << "B. 'Property<...>::value' priority examples:" << '\n'
              << '\n';

    std::cout << "1) print priority of unknown properties" << '\n';
    std::cout << Property<A>::value << " - A priority" << '\n';
    std::cout << Property<B>::value << " - B priority" << '\n';
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
