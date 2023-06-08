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
    x.getDmg();
    { x.getDmg() } -> std::convertible_to<Damage>;
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
    template <DamageAccessable T>
    static auto& get(T& el) {
        return el.dmg;
    }

    template <GetDamageAccessable T>
    static auto& get(T& el) {
        return el.getDmg();
    }

    template <CustomDamageAccessable T>
    static auto& get(T& el) {
        return customAccessDamage<T>::get(el);
    }

    template <CustomDamageAccessable T>
    static auto& get(const T& el) {
        return customAccessDamage<T>::get(el);
    }
};

}  // namespace traits
