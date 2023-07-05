#pragma once
#include <type_traits>

struct Protection;

template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(T x) {
    x.getProtection();
    { x.getProtection() } -> std::convertible_to<Protection>;
};

namespace traits {

template <typename T>
struct customAccessProtection {};

template <typename T>
concept CustomProtectionAccessable = requires(T x) {
    customAccessProtection<T>::get(x);
    { customAccessProtection<T>::get(x) } -> std::convertible_to<Protection>;
};

struct accessProtection {
    static auto& get(ProtectionAccessable auto& el) {
        return el.protection;
    }

    static auto& get(GetProtectionAccessable auto& el) {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
    static auto& get(T& el) {
        return customAccessProtection<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
