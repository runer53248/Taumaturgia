#pragma once
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/WearContainer/ArmorWearConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(ArmorWear, armorWear, WearContainer);
#else
struct accessArmorWear : public accessType<WearContainer> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessArmorWear, WearContainer>;

    template <ArmorWearAccessable T>
        requires(not accessType<WearContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.armorWear);
    }

    template <GetArmorWearAccessable T>
        requires(not accessType<WearContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getArmorWear();
    }

    using accessType<WearContainer>::get;
};
#endif

}  // namespace traits

template <>
struct trait_<WearContainer> {
    using type = traits::accessArmorWear;
};
