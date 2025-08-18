#pragma once
#include "Empty.hpp"

using Tile_list = properties_list<
    Naming,
    Damaging>;
using Tile_base = Empty<>;
using TileBuild = Tile_list::apply_ordered_properties_to<Tile_base>;

// using TileBuild = add_properties_ordered<
//     Empty<>,
//     Naming,
//     Damaging>;

struct TileClass {
    Name name;
    Damage dmg;
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES

static_assert(std::same_as<
              TileBuild,
              add_properties_ordered<
                  Empty<>,
                  Naming,
                  Damaging>>);
static_assert(std::same_as<
              TileBuild,
              properties_list<
                  Naming,
                  Damaging>::apply_ordered_properties_to<TileBuild>>);

using Tile = TileBuild;

template <typename T>
concept is_from_Tile =
    std::is_base_of_v<Tile_base, T>  //
    and std::same_as<
            T,
            Tile_list::apply_ordered_properties_to<T>>;

#else

using Tile = TileClass;

template <typename T>
concept is_from_Tile = std::is_base_of_v<Tile, T>;

#endif

static_assert(is_from_Tile<Tile>);

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
