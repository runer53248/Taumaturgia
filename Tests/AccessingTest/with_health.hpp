#pragma once
#include "Usage/With.hpp"

// MARK: with_health

struct with_health {
    Health hp;
};

template <typename T>
    requires std::is_base_of_v<with_health, T>
struct HoldTypes<T> {
    using types = list<Health>;
};

// template <typename TYPE, typename T>
//     requires std::is_base_of_v<with_health, T>
// struct traits::CustomAccessType<TYPE, T> {
//     static constexpr decltype(auto) get(auto& el) {
//         return (el.hp);
//     }
// };
