#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"

struct Empty {};

static_assert(std::is_same_v<
              A<A<A<Empty>>>,
              A<Empty>>);

template <typename T>
using BaseA = impl::A_<T>;

static_assert(derived_from_template_base<BaseA<Empty>, BaseA>);
static_assert(not derived_from_template_base<B<Empty>, BaseA>);
static_assert(derived_from_template_base<BaseA<B<Empty>>, BaseA>);
static_assert(derived_from_template_base<Living<B<BaseA<Empty>>>, BaseA>);
static_assert(derived_from_template_base<B<BaseA<Empty>>, BaseA>);
static_assert(not derived_from_template_base<Empty, BaseA>);

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
