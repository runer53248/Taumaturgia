#pragma once

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(ArmorWear, armorWear, WearContainer);
#else
struct accessArmorWear {
    static constexpr auto& get(ArmorWearAccessable auto& el) noexcept {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
        requires(not(CustomArmorWearAccessable<T> or GetTypeTemplateArmorWearAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
        requires(not GetTypeTemplateArmorWearAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessArmorWear<std::remove_cvref_t<T> >::get(el);
    }

    template <GetTypeTemplateArmorWearAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<WearContainer>();
    }
};
#endif

}  // namespace traits
