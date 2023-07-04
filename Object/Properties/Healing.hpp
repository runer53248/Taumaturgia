#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/HealStrategy.hpp"

template <typename T>
struct Healing_ : T {
    Healing_(const Name& name, Health&& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{std::move(cureHealth)} {}

    Healing_(const Name& name, const Health& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{cureHealth} {}

    auto& getCureHealth() {
        return cureHealth;
    }

    const auto& getCureHealth() const {
        return cureHealth;
    }

private:
    Health cureHealth{};
};

struct Healing_Test {};
static_assert(Healingable<Healing_<Healing_Test>>);

template <typename T>
using Healing = std::conditional_t<Healingable<T>, T, Healing_<T>>;

template <typename T>
struct HealStrategy_<Healing_<T>> : HealStrategy_<T> {};  // forward eventualy implemented strategy
