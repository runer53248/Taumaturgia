#pragma once
#include "helper/same_as_ref.hpp"

struct ProtectionContainer;

namespace traits {

template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), ProtectionContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getArmorWear() } -> same_as_ref<ProtectionContainer>;
    { std::as_const(x).getArmorWear() } -> same_as_ref<const ProtectionContainer>;
};

template <typename T>
struct CustomAccessArmorWear {};

template <typename T>
concept CustomArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessArmorWear<T>::get(x) } -> same_as_ref<ProtectionContainer>;
    { CustomAccessArmorWear<T>::get(std::as_const(x)) } -> same_as_ref<const ProtectionContainer>;
};

template <typename T>
concept UserTypeArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<ProtectionContainer>() } -> same_as_ref<ProtectionContainer>;
    { std::as_const(x).template getType<ProtectionContainer>() } -> same_as_ref<const ProtectionContainer>;
};

struct accessArmorWear {
    static auto& get(ArmorWearAccessable auto& el) {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
        requires(not(CustomArmorWearAccessable<T> or UserTypeArmorWearAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
        requires(not UserTypeArmorWearAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessArmorWear<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeArmorWearAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<ProtectionContainer>();
    }
};

}  // namespace traits
