#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class Health;

namespace traits {
namespace helpers {

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

}  // namespace helpers

struct accessHealth : public impl::accessType<Health> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessHealth, Health>;

    template <helpers::HealthAccessable T>
        requires(not accessType<Health>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.hp);
    }

    template <helpers::GetHealthAccessable T>
        requires(not accessType<Health>::accessable<T>)
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
