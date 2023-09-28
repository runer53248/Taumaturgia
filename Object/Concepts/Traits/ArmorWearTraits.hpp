#pragma once
#include "helper/same_as_ref.hpp"

struct ProtectionContainer;

template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), ProtectionContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(T x) {
    x.getArmorWear();
    { x.getArmorWear() } -> same_as_ref<ProtectionContainer>;
};

namespace traits {

template <typename T>
struct CustomAccessArmorWear {};

template <typename T>
concept CustomArmorWearAccessable = requires(T x) {
    CustomAccessArmorWear<T>::get(x);
    { CustomAccessArmorWear<T>::get(x) } -> same_as_ref<ProtectionContainer>;
};

struct accessArmorWear {
    static auto& get(ArmorWearAccessable auto& el) {
        return el.armorWear;
    }

    static auto& get(GetArmorWearAccessable auto& el) {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
    static auto& get(T& el) {
        return CustomAccessArmorWear<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
