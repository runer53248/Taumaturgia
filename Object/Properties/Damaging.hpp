#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/AttackStrategy.hpp"

template <typename T>
struct Damaging_ : T {
    template <typename... INFO>
        requires(std::is_constructible_v<Damage, INFO...> and sizeof...(INFO) > 0)
    Damaging_(const Name& name, std::tuple<INFO...>&& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::move(std::make_from_tuple<Damage>(std::forward<decltype(dmg)>(dmg)))} {
    }

    Damaging_(const Name& name, decltype(std::ignore), auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Damaging_(const Name& name, Damage&& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::move(dmg)} {}

    Damaging_(const Name& name, const Damage& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{dmg} {}

    auto& getDamage() {
        return dmg;
    }

    const auto& getDamage() const {
        return dmg;
    }

private:
    Damage dmg{};
};

namespace Test {
struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);
}  // namespace Test

template <typename T>
using Damaging = std::conditional_t<Damagingable<T>, T, Damaging_<T>>;

template <typename T>
struct AttackStrategy_<Damaging_<T>> : AttackStrategy_<T> {};  // forward eventualy implemented strategy
