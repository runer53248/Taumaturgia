#pragma once
#include "helper/same_as_ref.hpp"

struct Damage;

template <typename T>
concept DamageAccessable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};

template <typename T>
concept GetDamageAccessable = requires(T x) {
    x.getDamage();
    { x.getDamage() } -> same_as_ref<Damage>;
};

namespace traits {

template <typename T>
struct CustomAccessDamage {};

template <typename T>
concept CustomDamageAccessable = requires(T x) {
    CustomAccessDamage<T>::get(x);
    { CustomAccessDamage<T>::get(x) } -> same_as_ref<Damage>;
};

struct accessDamage {
    static auto& get(DamageAccessable auto& el) {
        return el.dmg;
    }

    static auto& get(GetDamageAccessable auto& el) {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
    static auto& get(T& el) {
        return CustomAccessDamage<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
