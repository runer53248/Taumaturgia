#pragma once
#include "Taumaturgia/Properties/access_features.hpp"

class Health;

namespace traits::helpers {

template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getHealth() } -> std::same_as<Health&>;
    { std::as_const(x).getHealth() } -> std::same_as<const Health&>;
};

}  // namespace traits::helpers

namespace traits {

struct accessHealth : public accessType<Health> {  // inheritance
    template <typename T>
    static const bool is_accessable = helpers::accessable<T, accessHealth, Health>;

    template <helpers::HealthAccessable T>
        requires(not accessType<Health>::is_accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.hp);
    }

    template <helpers::GetHealthAccessable T>
        requires(not accessType<Health>::is_accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getHealth();
    }

    using accessType<Health>::get;
};

}  // namespace traits

template <>
struct trait_<Health> {
    using type = traits::accessHealth;
};
