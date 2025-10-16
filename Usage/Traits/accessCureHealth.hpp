#pragma once
#include "Taumaturgia/Properties/access_features.hpp"

class CureHealth;

namespace traits::helpers {

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

}  // namespace traits::helpers

namespace traits {

struct accessCureHealth : public accessType<CureHealth> {  // inheritance
    template <typename T>
    static const bool is_accessable = helpers::accessable<T, accessCureHealth, CureHealth>;

    template <helpers::CureHealthAccessable T>
        requires(not accessType<CureHealth>::is_accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.cureHealth);
    }

    template <helpers::GetCureHealthAccessable T>
        requires(not accessType<CureHealth>::is_accessable<T>)
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
