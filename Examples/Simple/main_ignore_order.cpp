#ifdef WITH_ADD_PROPERTIES

#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/DefaultStrategies.hpp"

struct Empty {};

using Tile_list = properties_list<
    Naming,
    Damaging>;

using Tile = Tile_list::apply_properties_to<Empty>;
using Tile_2 = add_properties<
    Empty,
    Naming,
    Damaging>;
static_assert(std::same_as<Tile, Tile_2>);

using Tile_unordered = Tile_list::apply_unordered_properties_to<Empty>;
using Tile_unordered_2 = add_properties_unordered<
    Empty,
    Naming,
    Damaging>;
static_assert(std::same_as<Tile_unordered, Tile_unordered_2>);

static_assert(std::same_as<
              Tile,
              add_properties_unordered<
                  Tile,
                  Naming,
                  Damaging>>);
static_assert(std::same_as<
              Tile,
              properties_list<
                  Naming,
                  Damaging>::apply_properties_to<Tile>>);

static_assert(std::same_as<
              Tile_unordered,
              add_properties_unordered<
                  Tile_unordered,
                  Naming,
                  Damaging>>);
static_assert(std::same_as<
              Tile_unordered,
              properties_list<
                  Naming,
                  Damaging>::apply_unordered_properties_to<Tile_unordered>>);
static_assert(std::same_as<  // in this case order of properties don't change result
              properties_list<
                  Naming,
                  Damaging>::apply_unordered_properties_to<Tile_unordered>,
              properties_list<
                  Damaging,
                  Naming>::apply_unordered_properties_to<Tile_unordered>>);
static_assert(std::same_as<
              add_properties_unordered<
                  Empty,
                  Damaging,
                  Naming>,  // * <- 2
              properties_list<
                  Naming,                          // * <- 1
                  Damaging>::apply_properties_to<  // * ordered version moves Naming at end
                  add_properties_unordered<Empty,
                                           Naming,        // * <- 1
                                           Damaging>>>);  // ! error - changes order of properties in result

#endif

// fixed: add_properties and apply_properties_to don't remove duplicates when IGNORE_ORDER_LIST is defined

int main() {
    static_assert(not helpers::is_same_priority<Property<Naming>, Property<Damaging>>);
    static_assert(not helpers::is_same_priority<Property_unordered<Naming>, Property_unordered<Damaging>>);

    std::cout << "priority Property<Naming> = " << Property<Naming>::value << '\n';
    std::cout << "priority Property<Damaging> = " << Property<Damaging>::value << '\n';
    std::cout << "priority Property_unordered<Naming> = " << Property_unordered<Naming>::value << '\n';
    std::cout << "priority Property_unordered<Damaging> = " << Property_unordered<Damaging>::value << '\n';
    std::cout << "unordered_properties_counter = " << unordered_properties_counter << '\n'
              << '\n';

    static_assert(helpers::is_same_priority<Property<Damaging_impl>, Property<Damaging>>);
    static_assert(helpers::is_same_priority<Property<Naming_impl>, Property<Naming>>);
    std::cout << name<helpers::append_and_order_property_lists<
                     list<
                         Property<Damaging_impl>,
                         Property<Naming_impl>>,
                     list<
                         Property<Damaging>,
                         Property<Naming>>>>()
              << '\n';

    static_assert(helpers::is_same_priority<Property_unordered<Damaging_impl>, Property_unordered<Damaging>>);
    static_assert(helpers::is_same_priority<Property_unordered<Naming_impl>, Property_unordered<Naming>>);
    std::cout << name<helpers::append_and_order_property_lists<
                     list<
                         Property_unordered<Damaging_impl>,
                         Property_unordered<Naming_impl>>,
                     list<
                         Property_unordered<Damaging>,
                         Property_unordered<Naming>>>>()
              << '\n';

    std::cout << name<Property_unordered<Damaging>>()
              << '\n';
    std::cout << name<Property_unordered<Naming>>()
              << '\n';

    auto example_1_text = "add_properties_f<Empty, Naming, Naming, Damaging>";
    using example_1 = add_properties_unordered<Empty, Naming, Naming, Damaging>;

    std::cout << example_1_text << " = "
              << name<example_1>() << '\n'
              << '\n';

    std::cout << "add_properties_unordered<Tile, Damaging, Naming> = \n\t"
              << name<add_properties_unordered<Tile, Damaging, Naming>>()
              << '\n';
    std::cout << "add_properties<Tile, Damaging, Naming> = \n\t"
              << name<add_properties<Tile, Damaging, Naming>>()
              << '\n';
    std::cout << "add_properties_unordered<Tile, Naming, Naming, Damaging> = \n\t"
              << name<add_properties_unordered<Tile, Naming, Naming, Damaging>>()
              << '\n';
    std::cout << "properties_list<Naming, Naming, Damaging>::apply_unordered_properties_to<Tile>> = \n\t"
              << name<properties_list<Naming, Naming, Damaging>::apply_unordered_properties_to<Tile>>()
              << '\n';
    std::cout << "properties_list<Naming, Naming, Damaging>::apply_properties_to<Tile>> = \n\t"
              << name<properties_list<Naming, Naming, Damaging>::apply_properties_to<Tile>>() << '\n'
              << '\n';

    std::cout << "add_properties_unordered<Tile_unordered, Damaging, Naming> = \n\t"
              << name<add_properties_unordered<Tile_unordered, Damaging, Naming>>()
              << '\n';
    std::cout << "add_properties<Tile_unordered, Damaging, Naming> = \n\t"
              << name<add_properties<Tile_unordered, Damaging, Naming>>() << " !!! fix order"
              << '\n';
    std::cout << "add_properties_unordered<Tile_unordered, Naming, Naming, Damaging> = \n\t"
              << name<add_properties_unordered<Tile_unordered, Naming, Naming, Damaging>>()
              << '\n';
    std::cout << "properties_list<Naming, Naming, Damaging>::apply_unordered_properties_to<Tile_unordered>> = \n\t"
              << name<properties_list<Naming, Naming, Damaging>::apply_unordered_properties_to<Tile_unordered>>()
              << '\n';
    std::cout << "properties_list<Naming, Naming, Damaging>::apply_properties_to<Tile_unordered>> = \n\t"
              << name<properties_list<Naming, Naming, Damaging>::apply_properties_to<Tile_unordered>>() << " !!! fix order"
              << '\n';
}
