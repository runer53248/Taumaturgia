#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/AliveStrategy.hpp"

template <typename T>
struct Living_ : T {
    Living_(const Name& name, auto&& hp, auto&&... args)
        requires std::is_convertible_v<decltype(hp), Health>  // this requirement block implicit conversion for Health like: Living<...>{Name{""}, 1};
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::forward<decltype(hp)>(hp)} {}

    Health hp{};
};

struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);

template <typename T>
using Living = std::conditional_t<Livingable<T>, T, Living_<T>>;
