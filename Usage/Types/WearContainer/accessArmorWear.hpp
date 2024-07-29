#pragma once
#include "Taumaturgia/Traits/accessType.hpp"
#include "Usage/Types/WearContainer/ArmorWearConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(ArmorWear, armorWear, WearContainer);
#else
struct accessArmorWear : public accessType<WearContainer> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessArmorWear, WearContainer>;

    static constexpr auto& get(ArmorWearAccessable auto& el) noexcept {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getArmorWear();
    }

    using accessType<WearContainer>::get;
};
#endif

}  // namespace traits
