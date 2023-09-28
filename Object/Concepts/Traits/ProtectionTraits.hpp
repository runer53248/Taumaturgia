#pragma once
#include "helper/same_as_ref.hpp"

struct Protection;

template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(T x) {
    x.getProtection();
    { x.getProtection() } -> same_as_ref<Protection>;
};

namespace traits {

template <typename T>
struct CustomAccessProtection {};

template <typename T>
concept CustomProtectionAccessable = requires(T x) {
    CustomAccessProtection<T>::get(x);
    { CustomAccessProtection<T>::get(x) } -> same_as_ref<Protection>;
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
        return CustomAccessProtection<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
