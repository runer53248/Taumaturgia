#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"

#include "Usage/DefaultStrategies.hpp"
#include "Usage/Properties.hpp"

// MARK: Item

struct Item {
    std::string name;
    Health hp;
};

struct Tile {
    std::string name;
    Health hp;
};

template <>
struct GetStrategy_<Item> {
    template <Properties PROPERTY>
    constexpr auto operator()(Gettingable auto& obj) const {
        if constexpr (PROPERTY == Properties::Health) {
            std::cout << 'x';
            return default_get_behavior<Properties::Health>(obj);
        } else {
            return default_get_behavior<PROPERTY>(obj);
        }
    }
};

using Item_2 = Living<Naming<Item>>;
static_assert(std::is_same_v<Item, Item_2>);

static_assert(Gettingable<Item>);
static_assert(is_custom_get_strategy<Item>);

static_assert(Gettingable<Tile>);
static_assert(not is_custom_get_strategy<Tile>);

// MARK: main

int main() {
    auto item = Item{
        Name{"Book"},
        Health{30}};

    auto tile = Tile{
        Name{"Grass"},
        Health{30}};

    Object obj(item);
    Object obj_2(tile);

    obj.getOpt<Properties::Health>();
    obj_2.getOpt<Properties::Health>();
    std::cout << '\n';

    print_object_properties(item);
    print_object(item);

    print_object_properties(tile);
    print_object(tile);
}
