#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"
#include "Usage/Properties.hpp"

// MARK: Item

struct Item {
    std::string name;
    Health hp;
    Damage dmg{3};
};

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

static_assert(std::is_same_v<Item, Living<Naming<Item>>>);

static_assert(Gettingable<Item>);
static_assert(is_custom_get_strategy<Item>);
static_assert(not is_custom_alive_strategy<Item>);

// MARK: Tile

struct Tile {
    std::string name;
    Damage dmg{3};
};

struct LivingTile : Tile {
    Health hp{30};
};

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

static_assert(Gettingable<Tile>);
static_assert(not is_custom_get_strategy<Tile>);
static_assert(is_custom_alive_strategy<Tile>);

static_assert(Gettingable<LivingTile>);
static_assert(not is_custom_get_strategy<LivingTile>);
static_assert(is_custom_alive_strategy<LivingTile>);

// MARK: main

int main() {
    auto item = Item{
        Name{"Book"},
        Health{30}};

    auto tile = Tile{
        Name{"Tile"}};

    auto living_tile = LivingTile{
        Name{"Grass"},
        Damage{0, Effect{EffectType::Burn}},
        Health{60}};

    Object obj(item);
    Object obj_2(tile);
    Object obj_3(living_tile);

    obj.getOpt<Properties::Health>();
    obj_2.getOpt<Properties::Health>();
    std::cout << '\n';

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
