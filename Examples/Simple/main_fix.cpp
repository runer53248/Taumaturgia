#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"
#include "Usage/Properties.hpp"

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
    std::string name;
    Damage dmg;
};
struct LivingTile : Tile {
    Health hp;
};
#endif

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
}
