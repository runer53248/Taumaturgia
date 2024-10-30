#pragma once

#ifdef WITH_ADD_PROPERTIES

#include "Empty.hpp"

using Tile_list = properties_list<
    Naming,
    Damaging>;
using Tile_base = Empty<>;
using Tile = Tile_list::apply_properties_to<Tile_base>;

// using Tile = add_properties<
//     Empty<>,
//     Naming,
//     Damaging>;

template <typename T>
concept is_from_Tile =
    std::is_base_of_v<Tile_base, T>  //
    and std::same_as<
            T,
            Tile_list::apply_properties_to<T>>;

static_assert(std::same_as<
              Tile,
              add_properties<
                  Empty<>,
                  Naming,
                  Damaging>>);
static_assert(std::same_as<
              Tile,
              properties_list<
                  Naming,
                  Damaging
                >::apply_properties_to<Tile>>);

static_assert(is_from_Tile<Tile>);

#else

struct Tile {
    Name name;
    Damage dmg;
};

template <typename T>
concept is_from_Tile = std::is_base_of_v<Tile, T>;

static_assert(is_from_Tile<Tile>);

#endif

// MARK: AliveStrategy_<T>

template <typename T>
// requires std::is_base_of_v<Tile, T>
    requires is_from_Tile<T>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Health, T> {
#else
struct AliveStrategy_<T> {
#endif
    static constexpr std::optional<AliveStatus> operator()(Livingable auto&) {  // when have Livingable properties
        std::cout << " [play death]";
        return AliveStatus::Death;
    }

    static constexpr std::optional<AliveStatus> operator()(auto&) {  // when not have Livingable properties
        std::cout << " [imitating living]";
        return AliveStatus::Living;
    }
};

// MARK: GetterStrategy_<T>

template <typename T>
// requires std::is_base_of_v<Tile, T>
    requires is_from_Tile<T>
struct GetterStrategy_<T> {
    template <Properties PROPERTY>
    static constexpr auto operator()(Gettingable auto& obj) {
        if constexpr (PROPERTY == Properties::Health) {
            std::cout << 'H';
        } else if constexpr (PROPERTY == Properties::Damage) {
            std::cout << 'D';
        } else {
            std::cout << 'V';
        }
        return default_get_behavior<PROPERTY>(obj);
    }
};

static_assert(Gettingable<Tile>);
// static_assert(is_custom_get_strategy<Tile>);
// static_assert(is_custom_alive_strategy<Tile>);
