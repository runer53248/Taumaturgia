#pragma once
#include "helper/same_as_ref.hpp"

struct ProtectionContainer;

template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), ProtectionContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getArmorWear() } -> same_as_ref<ProtectionContainer>;
    { y.getArmorWear() } -> same_as_ref<const ProtectionContainer>;
};

namespace traits {

template <typename T>
struct CustomAccessArmorWear {};

template <typename T>
concept CustomArmorWearAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessArmorWear<T>::get(x) } -> same_as_ref<ProtectionContainer>;
    { CustomAccessArmorWear<T>::get(y) } -> same_as_ref<const ProtectionContainer>;
};

struct accessArmorWear {
    static auto& get(ArmorWearAccessable auto& el) {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
        requires(not CustomArmorWearAccessable<T>)  // use custom access if available
    static decltype(auto) get(T& el) {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
    static decltype(auto) get(T& el) {
        return CustomAccessArmorWear<std::remove_cv_t<T>>::get(el);
    }

    template <CustomArmorWearAccessable T>
    static decltype(auto) get(const T& el) {
        return CustomAccessArmorWear<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
