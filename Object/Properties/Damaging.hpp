#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/AttackStrategy.hpp"

template <typename T>
struct Damaging_ : T {
    Damaging_(const Name& name, auto&& dmg, auto&&... args)
        requires std::is_convertible_v<Damage, decltype(dmg)>
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::forward<decltype(dmg)>(dmg)} {}

    Damage dmg{};
};

struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);

template <typename T>
using Damaging = std::conditional_t<Damagingable<T>, T, Damaging_<T>>;

template <typename T>
struct AttackStrategy_<Damaging_<T>> : AttackStrategy_<T> {};  // forward eventualy implemented strategy
