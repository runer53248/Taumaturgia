#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/DefendStrategy.hpp"

template <typename T>
struct Protecting_ : T {
    Protecting_(const Name& name, Protection&& protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, protection{std::move(protection)} {}

    Protecting_(const Name& name, const Protection& protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, protection{protection} {}

    auto& getProtection() {
        return protection;
    }

    const auto& getProtection() const {
        return protection;
    }

private:
    Protection protection{};
};

struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, Protecting_<T>>;

template <typename T>
struct DefendStrategy_<Protecting_<T>> : DefendStrategy_<T> {};  // forward eventualy implemented strategy
