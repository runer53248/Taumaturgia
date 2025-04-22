#pragma once
#include "Taumaturgia/Traits/trait.hpp"

class Damage;

namespace traits::helpers {

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

}  // namespace traits::helpers

namespace traits {

struct accessDamage /*: public accessType<Damage>*/ {
    using general_access_type = accessType<Damage>;  // composition
    template <typename T>
    static const bool general_accessable = general_access_type::is_accessable<T>;

    template <typename T>
    static constexpr bool is_accessable = helpers::accessable<T, accessDamage, Damage> or general_accessable<T>;

    template <helpers::DamageAccessable T>
        requires(not(helpers::GetDamageAccessable<T> or CustomAccessType_able<T, Damage>))  // prefer getDamage() when both dmg and getDamage() are visible
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.dmg);
    }

    template <helpers::GetDamageAccessable T>
        requires(not CustomAccessType_able<T, Damage>)  // prefer custom access more
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    // using accessType<Damage>::get;

    template <typename T>
        requires((not(helpers::DamageAccessable<T> or helpers::GetDamageAccessable<T>) and general_accessable<T>) or CustomAccessType_able<T, Damage>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return general_access_type::get(el);
    }
};

}  // namespace traits

template <>
struct trait_<Damage> {
    using type = traits::accessDamage;
};
