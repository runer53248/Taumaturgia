#pragma once
#include "Behaviors/default_get_behavior.hpp"

template <>
struct GetStrategy_<Default> {
    template <Properties PROPERTY>
    constexpr auto operator()(Gettingable auto& obj) const {
        return default_get_behavior<PROPERTY>(obj);
    }
};
