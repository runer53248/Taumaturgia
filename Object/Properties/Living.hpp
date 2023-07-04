#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/AliveStrategy.hpp"

template <typename T>
struct Living_ : T {
    Living_(const Name& name, Health&& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::move(hp)} {}

    Living_(const Name& name, const Health& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{hp} {}

    auto& getHp() {
        return hp;
    }

    const auto& getHp() const {
        return hp;
    }

private:
    Health hp{};
};

struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);

template <typename T>
using Living = std::conditional_t<Livingable<T>, T, Living_<T>>;
