#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class EffectTypeContainer;

namespace traits {

namespace helpers {

template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getRestoreEffects() } -> std::same_as<EffectTypeContainer&>;
    { std::as_const(x).getRestoreEffects() } -> std::same_as<const EffectTypeContainer&>;
};

}  // namespace helpers

struct accessRestoreEffects : public impl::accessType<EffectTypeContainer> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessRestoreEffects, EffectTypeContainer>;

    template <helpers::RestoreEffectsAccessable T>
        requires(not accessType<EffectTypeContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.restoreEffects);
    }

    template <helpers::GetRestoreEffectsAccessable T>
        requires(not accessType<EffectTypeContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getRestoreEffects();
    }

    using accessType<EffectTypeContainer>::get;
};

}  // namespace traits

template <>
struct trait_<EffectTypeContainer> {
    using type = traits::accessRestoreEffects;
};
