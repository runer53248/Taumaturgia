#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class WearContainer;

namespace traits {

namespace helpers {

template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), WearContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getArmorWear() } -> std::same_as<WearContainer&>;
    { std::as_const(x).getArmorWear() } -> std::same_as<const WearContainer&>;
};

}  // namespace helpers

struct accessArmorWear : public impl::accessType<WearContainer> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessArmorWear, WearContainer>;

    template <helpers::ArmorWearAccessable T>
        requires(not accessType<WearContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.armorWear);
    }

    template <helpers::GetArmorWearAccessable T>
        requires(not accessType<WearContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getArmorWear();
    }

    using accessType<WearContainer>::get;
};

}  // namespace traits

template <>
struct trait_<WearContainer> {
    using type = traits::accessArmorWear;
};
