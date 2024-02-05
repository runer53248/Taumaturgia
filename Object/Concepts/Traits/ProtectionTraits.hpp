#pragma once
#include "helper/same_as_ref.hpp"

struct Protection;

namespace traits {

template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getProtection() } -> same_as_ref<Protection>;
    { y.getProtection() } -> same_as_ref<const Protection>;
};

template <typename T>
struct CustomAccessProtection {};

template <typename T>
concept CustomProtectionAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessProtection<T>::get(x) } -> same_as_ref<Protection>;
    { CustomAccessProtection<T>::get(y) } -> same_as_ref<const Protection>;
};

template <typename T>
concept UserTypeProtectionAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<Protection>() } -> same_as_ref<Protection>;
    { y.template getType<Protection>() } -> same_as_ref<const Protection>;
};

struct accessProtection {
    static auto& get(ProtectionAccessable auto& el) {
        return el.protection;
    }

    template <GetProtectionAccessable T>
        requires(not CustomProtectionAccessable<T> and not UserTypeProtectionAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
        requires(not UserTypeProtectionAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessProtection<std::remove_cv_t<T>>::get(el);
    }

    template <CustomProtectionAccessable T>
        requires(not UserTypeProtectionAccessable<T>)
    static decltype(auto) get(const T& el) {
        return CustomAccessProtection<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeProtectionAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Protection>();
    }

    template <UserTypeProtectionAccessable T>
    static decltype(auto) get(const T& el) {
        return el.template getType<Protection>();
    }
};

}  // namespace traits
