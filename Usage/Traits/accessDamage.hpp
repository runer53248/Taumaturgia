#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class Damage;

namespace traits {

template <typename T>
concept DamageAccessable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};

template <typename T>
concept GetDamageAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getDamage() } -> std::same_as<Damage&>;
    { std::as_const(x).getDamage() } -> std::same_as<const Damage&>;
};

struct accessDamage : public impl::accessType<Damage> {
    template <typename T>
    static constexpr bool accessable = helpers::trait_accessable<T, accessDamage, Damage>;

    template <DamageAccessable T>
        requires(not accessType<Damage>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.dmg);
    }

    template <GetDamageAccessable T>
        requires(not accessType<Damage>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    using accessType<Damage>::get;
};

}  // namespace traits

template <>
struct trait_<Damage> {
    using type = traits::accessDamage;
};
