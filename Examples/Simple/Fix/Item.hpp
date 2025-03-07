#pragma once
#include "Empty.hpp"

using ItemBuild = add_properties_ordered<
    Empty<struct ItemTag>,
    Naming,
    Living,
    Damaging>;

struct ItemClass {
    std::string name;
    Health hp;
    Damage dmg;
};

#ifdef WITH_ADD_PROPERTIES
using Item = ItemBuild;
#else
using Item = ItemClass;
#endif

// MARK: GetterStrategy_<Item>

template <>
struct GetterStrategy_<Item> {
    template <Properties PROPERTY>
    static constexpr auto operator()(Gettingable auto& obj) {
        if constexpr (PROPERTY == Properties::Health) {
            std::cout << "Hp";
        } else {
            std::cout << "Oth";
        }
        return default_get_behavior<PROPERTY>(obj);
    }
};

static_assert(Gettingable<Item>);
static_assert(is_custom_get_strategy<Item>);
static_assert(not is_custom_alive_strategy<Item>);
