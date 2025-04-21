#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/DefaultStrategies.hpp"

#include "Item.hpp"
#include "LivingTile.hpp"
#include "Tile.hpp"
#include "WeirdTile.hpp"

// MARK: main

#ifdef WITH_ADD_PROPERTIES
#ifndef IGNORE_ORDER_LIST
#define ARGUMENTS_REORDERED
#endif
#endif

int main() {
    const auto item = Item{
        Name{"Book"},
        Health{30},
        Damage{3}};

    const auto tile = Tile{
        Name{"Tile"},
        Damage{3}};

#ifdef ARGUMENTS_REORDERED
    std::cout << "\nARGUMENTS REORDERED\n\n";
    const auto living_tile = LivingTile{
        Name{"LivingTile"},
        Health{160},
        Damage{0, Effect{EffectType::Burn}}};
#else
    std::cout << "\nARGUMENTS AS GIVEN\n\n";
    const auto living_tile = LivingTile{
        Name{"LivingTile"},
        Damage{0, Effect{EffectType::Burn}},  // ! Damage is part of Tile struct and cant't be reordered in layout
        Health{60}};                          // ! or IGNORE_ORDER_LIST is defined and Living property is added last
#endif

    const auto weird_tile = WeirdTile{
        Name{"Grass"},
        Damage{3}};

    std::cout << '\n'
              << "compare tile and living_tile: \n"
              << name<decltype(tile)>() << '\n'
              << name<decltype(living_tile)>() << '\n'
              << '\n';
    std::cout << '\n'
              << "weird_tile: \n"
              << name<decltype(weird_tile)>() << '\n'
              << '\n';

    print_properties(item);
    print_object(item);

    print_properties(tile);
    print_object(tile);

    print_properties(living_tile);
    print_object(living_tile);

    std::cout << '\n';

    static_assert(std::is_same_v<
                  get_result_type<Properties::Health>,
                  add_optional_ref_wrapper<Health>>);
    static_assert(std::is_same_v<
                  get_result_type<Properties::Health, true>,
                  add_optional_ref_wrapper<const Health>>);

    static_assert(not is_properties_accessable<Properties::Health, Tile>);
    static_assert(is_properties_accessable<Properties::Health, LivingTile>);

    static_assert(is_properties_accessable<Properties::Name, Tile>);
    static_assert(is_properties_accessable<Properties::Name, LivingTile>);

    static_assert(properties_trait<Properties::Name>::template accessable<Tile>);
    static_assert(properties_trait<Properties::Name>::template accessable<LivingTile>);

    std::optional health_result = action_impl::get_impl(tile, DeduceProperties::Health);
    std::cout << '\n';
    std::cout << "health_result has_value  = " << health_result.has_value() << '\n';
    std::cout << "health_result type  = " << name<decltype(health_result)>() << '\n';

    std::optional item_health_result = action_impl::get_impl(item, DeduceProperties::Health);
    std::optional item_health_result_2 = action_impl::get_impl(item, Properties::Health);
    static_assert(not std::same_as<decltype(item_health_result), decltype(item_health_result_2)>);
    std::cout << '\n'
              << '\n'
              << "item_health_result (sProperties) = "
              << name<decltype(item_health_result)>() << '\n';
    std::cout << "item_health_result_2 (Properties) = "
              << name<decltype(item_health_result_2)>() << '\n'
              << '\n';

    std::optional damage_result = action_impl::get_impl(tile, DeduceProperties::Damage);
    std::optional name_result = action_impl::get_impl(tile, DeduceProperties::Name);  // return value only if type is Name
    std::cout << '\n';
    std::cout << "item_health_result = "
              << name<decltype(item_health_result)>() << '\n';
    std::cout << "damage_result = "
              << name<decltype(damage_result)>() << '\n';
    std::cout << "name_result = "
              << name<decltype(name_result)>() << '\n';
    if (name_result) {
        std::cout << "name = " << name_result.value() << '\n';
    }
    std::cout << "name = "
              << properties_trait<Properties::Name>::get(tile) << '\n'  // return value if type is Name or std::string
              << '\n';
    std::cout << "name trait type = "
              << name<decltype(properties_trait<Properties::Name>::get(tile))>() << '\n'
              << '\n';

    std::cout << "Protection trait type = "
              << name<decltype(action_impl::get_impl(tile, DeduceProperties::Protection))>() << '\n'  // return void
              << '\n';

    std::optional name_result_2 = action_impl::get_impl(tile, Properties::Name);

    std::cout << '\n'
              << "name_result_2 = "
              << name<decltype(name_result_2)>() << '\n';
    std::cout << '\n'
              << "name_result_2_unpack = "
              << name<unpack_to_list_t<decltype(name_result_2)>>() << '\n';
}
