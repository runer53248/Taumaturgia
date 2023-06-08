#pragma once
#include <type_traits>

struct ProtectionContainer;

template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), ProtectionContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(T x) {
    x.getArmorWear();
    { x.getArmorWear() } -> std::convertible_to<ProtectionContainer>;
};

namespace traits {

template <typename T>
struct customAccessArmorWear {};

template <typename T>
concept CustomArmorWearAccessable = requires(T x) {
    customAccessArmorWear<T>::get(x);
    { customAccessArmorWear<T>::get(x) } -> std::convertible_to<ProtectionContainer>;
};

struct accessArmorWear {
    template <ArmorWearAccessable T>
    static auto& get(T& el) {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
    static auto& get(T& el) {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
    static auto& get(T& el) {
        return customAccessArmorWear<T>::get(el);
    }

    template <CustomArmorWearAccessable T>
    static auto& get(const T& el) {
        return customAccessArmorWear<T>::get(el);
    }
};

}  // namespace traits
