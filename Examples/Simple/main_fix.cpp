#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"

// MARK: Empty

#ifdef WITH_ADD_PROPERTIES
template <typename TAG = void, typename... TAGS>
struct Empty {};
#endif

// MARK: Item

#ifdef WITH_ADD_PROPERTIES
using Item = add_properties<Empty<struct ItemTag>, Naming, Living, Damaging>;
#else
struct Item {
    std::string name;
    Health hp;
    Damage dmg;
};
#endif

// MARK: GetStrategy_<Item>

template <>
struct GetStrategy_<Item> {
    template <Properties PROPERTY>
    constexpr auto operator()(Gettingable auto& obj) const {
        if constexpr (PROPERTY == Properties::Health) {
            std::cout << 'x';
            return default_get_behavior<Properties::Health>(obj);
        } else {
            std::cout << 'y';
            return default_get_behavior<PROPERTY>(obj);
        }
    }
};

static_assert(Gettingable<Item>);
static_assert(is_custom_get_strategy<Item>);
static_assert(not is_custom_alive_strategy<Item>);

// MARK: Tile

#ifdef WITH_ADD_PROPERTIES
using Tile = add_properties<Empty<>, Naming, Damaging>;
using LivingTile = add_properties<Tile, Living>;
#else
struct Tile {
    Name name;
    Damage dmg;
};
struct LivingTile : Tile {
    Health hp;
};
#endif

// MARK: AliveStrategy_<T>

template <typename T>
    requires std::is_base_of_v<Tile, T>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Health, T> {
#else
struct AliveStrategy_<T> {
#endif
    constexpr std::optional<AliveStatus> operator()(Livingable auto&) const {  // when have Livingable properties
        std::cout << " [play death]";
        return AliveStatus::Death;
    }

    constexpr std::optional<AliveStatus> operator()(auto&) const {  // when not have Livingable properties
        std::cout << " [imitating living]";
        return AliveStatus::Living;
    }
};

// MARK: GetStrategy_<T>

template <typename T>
    requires std::is_base_of_v<Tile, T>
struct GetStrategy_<T> {
    template <Properties PROPERTY>
    constexpr auto operator()(Gettingable auto& obj) const {
        if constexpr (PROPERTY == Properties::Health) {
            std::cout << 'H';
            return default_get_behavior<Properties::Health>(obj);
        } else if constexpr (PROPERTY == Properties::Damage) {
            std::cout << 'D';
            return default_get_behavior<Properties::Damage>(obj);
        } else {
            std::cout << 'V';
            return default_get_behavior<PROPERTY>(obj);
        }
    }
};

static_assert(Gettingable<Tile>);
static_assert(is_custom_get_strategy<Tile>);
static_assert(is_custom_alive_strategy<Tile>);

static_assert(Gettingable<LivingTile>);
static_assert(is_custom_get_strategy<LivingTile>);
static_assert(is_custom_alive_strategy<LivingTile>);

// MARK: main

#include "Examples/demangle_type_name.hpp"

int main() {
    auto item = Item{
        Name{"Book"},
        Health{30},
        Damage{3}};

    auto tile = Tile{
        Name{"Tile"},
        Damage{3}};

    auto living_tile = LivingTile{
        Name{"Grass"},
#ifdef WITH_ADD_PROPERTIES
        Health{160},
        Damage{0, Effect{EffectType::Burn}}
#else
        Damage{0, Effect{EffectType::Burn}},
        Health{60}
#endif
    };

    print_object_properties(item);
    print_customized_properties(item);
    print_object(item);

    print_object_properties(tile);
    print_customized_properties(tile);
    print_object(tile);

    print_object_properties(living_tile);
    print_customized_properties(living_tile);
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

    std::optional health_result = action_impl::get_impl(item, sProperties<Properties::Health>{});
    std::optional damage_result = action_impl::get_impl(tile, sProperties<Properties::Damage>{});
    std::optional name_result = action_impl::get_impl(tile, sProperties<Properties::Name>{});  // return value only if type is Name
    std::cout << '\n';
    std::cout << "health_result = "
              << name<decltype(health_result)>() << '\n';
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
              << name<decltype(action_impl::get_impl(tile, sProperties<Properties::Protection>{}))>() << '\n'  // return void
              << '\n';

    std::optional name_result_2 = action_impl::get_impl(tile, Properties::Name);

    std::cout << '\n'
              << "name_result_2 = "
              << name<decltype(name_result_2)>() << '\n';
    std::cout << '\n'
              << "name_result_2_unpack = "
              << name<unpack_to_list_t<decltype(name_result_2)>>() << '\n';
}
