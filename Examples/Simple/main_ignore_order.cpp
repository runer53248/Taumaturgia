#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/DefaultStrategies.hpp"

struct Empty {};
using Tile_list = properties_list<
    Naming,
    Damaging>;

using Tile = Tile_list::apply_ordered_properties_to<Empty>;
using Tile_unordered = Tile_list::apply_unordered_properties_to<Empty>;

#include "order_assertions.hpp"

int main() {
    static_assert(not helpers::is_same_priority<Property<Naming>, Property<Damaging>>);
    static_assert(not helpers::is_same_priority<Property_unordered<Naming>, Property_unordered<Damaging>>);

    std::cout << "priority Property<Naming> = " << Property<Naming>::value << '\n';
    std::cout << "priority Property<Damaging> = " << Property<Damaging>::value << '\n';
    std::cout << "priority Property_unordered<Naming> = " << Property_unordered<Naming>::value << '\n';
    std::cout << "priority Property_unordered<Damaging> = " << Property_unordered<Damaging>::value
              << "\n\n";

    static_assert(helpers::is_same_priority<
                  Property<Damaging_impl>,
                  Property<Damaging>>);

    static_assert(helpers::is_same_priority<
                  Property_unordered<Damaging_impl>,
                  Property_unordered<Damaging>>);

    using list_of_impl_short = list<
        Property<Damaging_impl>,
        Property<Naming_impl>>;
    using list_of_alias_long = list<
        Property<Damaging>,
        Property<Naming>,
        Property<Living>>;
    std::cout << "list of impl followed by list of alias = \n\t"
              << name<helpers::append_and_order_property_lists<
                     list_of_impl_short,
                     list_of_alias_long>>()
              << "\n\n";

    using list_of_alias_short = list<
        Property<Damaging>,
        Property<Naming>>;
    using list_of_impl_long = list<
        Property<Damaging_impl>,
        Property<Naming_impl>,
        Property<Living_impl>>;
    std::cout << "list of alias followed by list of impl  = \n\t"
              << name<helpers::append_and_order_property_lists<
                     list_of_alias_short,
                     list_of_impl_long>>()
              << "\n\n";

    std::cout << "unordered list of impl followed by list of alias  = \n\t"
              << name<helpers::append_and_order_property_lists<
                     list<
                         Property_unordered<Damaging_impl>,
                         Property_unordered<Naming_impl>>,
                     list<
                         Property_unordered<Healing>,
                         Property_unordered<Damaging>,
                         Property_unordered<Naming>,
                         Property_unordered<Living>>>>()
              << "\n\n";
    std::cout << "mixed order list of impl followed by list of alias  = \n\t"
              << name<helpers::append_and_order_property_lists<
                     list<
                         Property_unordered<Damaging_impl>,
                         Property<Naming_impl>>,
                     list<
                         Property<Healing>,
                         Property_unordered<Damaging>,
                         Property_unordered<Naming>,
                         Property_unordered<Living>>>>()
              << "\n\n";

    std::cout << "add_properties_f<Empty, Naming, Naming, Damaging> = \n\t"
              << name<add_properties_unordered<Empty, Naming, Naming, Damaging>>()
              << "\n\n";

    std::cout << "TILE:\n";
    std::cout << "add_properties_unordered<Tile, Damaging, Naming> = \n\t"
              << name<add_properties_unordered<Tile, Damaging, Naming>>()
              << "\n";
    std::cout << "add_properties_ordered<Tile, Damaging, Naming> = \n\t"
              << name<add_properties_ordered<Tile, Damaging, Naming>>()
              << "\n";
    std::cout << "add_properties_unordered<Tile, Naming, Naming, Damaging> = \n\t"
              << name<add_properties_unordered<Tile, Naming, Naming, Damaging>>()
              << "\n";
    std::cout << "properties_list<>::apply_unordered_properties_to<Tile>> = \n\t"
              << name<properties_list<>::apply_unordered_properties_to<Tile>>()
              << "\n";
    std::cout << "properties_list<>::apply_ordered_properties_to<Tile>> = \n\t"
              << name<properties_list<>::apply_ordered_properties_to<Tile>>()
              << "\n\n";

    std::cout << "TILE UNORDERED:\n";
    std::cout << "add_properties_unordered<Tile_unordered, Damaging, Naming> = \n\t"
              << name<add_properties_unordered<Tile_unordered, Damaging, Naming>>()
              << "\n";
    std::cout << "add_properties_ordered<Tile_unordered, Damaging, Naming> = \n\t"
              << name<add_properties_ordered<Tile_unordered, Damaging, Naming>>()
              << "\n";
    std::cout << "add_properties_unordered<Tile_unordered, Naming, Naming, Damaging> = \n\t"
              << name<add_properties_unordered<Tile_unordered, Naming, Naming, Damaging>>()
              << "\n";
    std::cout << "properties_list<>::apply_unordered_properties_to<Tile_unordered>> = \n\t"
              << name<properties_list<>::apply_unordered_properties_to<Tile_unordered>>()
              << "\n";
    std::cout << "properties_list<>::apply_ordered_properties_to<Tile_unordered>> = \n\t"
              << name<properties_list<>::apply_ordered_properties_to<Tile_unordered>>()
              << "\n\n";
}
