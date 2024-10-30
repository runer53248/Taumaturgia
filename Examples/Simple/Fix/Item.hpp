#pragma once

#ifdef WITH_ADD_PROPERTIES

#include "Empty.hpp"

using Item = add_properties<
    Empty<struct ItemTag>,
    Naming,
    Living,
    Damaging>;

#else

struct Item {
    std::string name;
    Health hp;
    Damage dmg;
};

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
