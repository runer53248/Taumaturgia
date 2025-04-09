#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class Damage;

namespace traits {

namespace helpers {

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

}  // namespace helpers

struct accessDamage /*: public accessType<Damage>*/ {
    using general_access_type = accessType<Damage>;
    template <typename T>
    static const bool general_accessable = general_access_type::accessable<T>;

    template <typename T>
    static constexpr bool accessable = helpers::trait_accessable<T, accessDamage, Damage> or general_accessable<T>;

    template <helpers::DamageAccessable T>
    // requires(not accessType<Damage>::accessable<T>)
        requires(not(helpers::GetDamageAccessable<T> or helpers::CustomTypeAccessable<T, Damage>))  // prefer getDamage() when both dmg and getDamage() are visible
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.dmg);
    }

    template <helpers::GetDamageAccessable T>
    // requires(not accessType<Damage>::accessable<T>)
        requires(not helpers::CustomTypeAccessable<T, Damage>)  // prefer custom access more
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    // using accessType<Damage>::get;

    template <typename T>
        requires((not(helpers::DamageAccessable<T> or helpers::GetDamageAccessable<T>) and general_accessable<T>) or helpers::CustomTypeAccessable<T, Damage>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return general_access_type::get(el);
    }
};

}  // namespace traits

template <>
struct trait_<Damage> {
    using type = traits::accessDamage;
};
