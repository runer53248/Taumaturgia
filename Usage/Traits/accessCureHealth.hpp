#pragma once
#include "Taumaturgia/Traits/trait.hpp"

class CureHealth;

namespace traits {

namespace helpers {

template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), CureHealth>;
};

template <typename T>
concept GetCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getCureHealth() } -> std::same_as<CureHealth&>;
    { std::as_const(x).getCureHealth() } -> std::same_as<const CureHealth&>;
};

}  // namespace helpers

struct accessCureHealth : public accessType<CureHealth> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessCureHealth, CureHealth>;

    template <helpers::CureHealthAccessable T>
        requires(not accessType<CureHealth>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.cureHealth);
    }

    template <helpers::GetCureHealthAccessable T>
        requires(not accessType<CureHealth>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    using accessType<CureHealth>::get;
};

}  // namespace traits

template <>
struct trait_<CureHealth> {
    using type = traits::accessCureHealth;
};
