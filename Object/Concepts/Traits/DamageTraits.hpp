#pragma once
#include "helper/same_as_ref.hpp"

struct Damage;

template <typename T>
concept DamageAccessable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};

template <typename T>
concept GetDamageAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getDamage() } -> same_as_ref<Damage>;
    { y.getDamage() } -> same_as_ref<const Damage>;
};

namespace traits {

template <typename T>
struct CustomAccessDamage {};

template <typename T>
concept CustomDamageAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessDamage<T>::get(x) } -> same_as_ref<Damage>;
    { CustomAccessDamage<T>::get(y) } -> same_as_ref<const Damage>;
};

struct accessDamage {
    static auto& get(DamageAccessable auto& el) {
        return el.dmg;
    }

    template <GetDamageAccessable T>
        requires(not CustomDamageAccessable<T>)  // use custom access if available
    static decltype(auto) get(T& el) {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
    static decltype(auto) get(T& el) {
        return CustomAccessDamage<std::remove_cv_t<T>>::get(el);
    }

    template <CustomDamageAccessable T>
    static decltype(auto) get(const T& el) {
        return CustomAccessDamage<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
