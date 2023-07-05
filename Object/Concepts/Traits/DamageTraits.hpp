#pragma once
#include <type_traits>

struct Damage;

template <typename T>
concept DamageAccessable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};

template <typename T>
concept GetDamageAccessable = requires(T x) {
    x.getDamage();
    { x.getDamage() } -> std::convertible_to<Damage>;
};

namespace traits {

template <typename T>
struct customAccessDamage {};

template <typename T>
concept CustomDamageAccessable = requires(T x) {
    customAccessDamage<T>::get(x);
    { customAccessDamage<T>::get(x) } -> std::convertible_to<Damage>;
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
        return customAccessDamage<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
