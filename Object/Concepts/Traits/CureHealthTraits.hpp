#pragma once
#include <type_traits>

struct Health;

template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), Health>;
};

template <typename T>
concept GetCureHealthAccessable = requires(T x) {
    x.getCureHealth();
    { x.getCureHealth() } -> std::convertible_to<Health>;
};

namespace traits {

template <typename T>
struct customAccessCureHealth {};

template <typename T>
concept CustomCureHealthAccessable = requires(T x) {
    customAccessCureHealth<T>::get(x);
    { customAccessCureHealth<T>::get(x) } -> std::convertible_to<Health>;
};

struct accessCureHealth {
    template <CureHealthAccessable T>
    static auto& get(T& el) {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
    static auto& get(T& el) {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
    static auto& get(T& el) {
        return customAccessCureHealth<T>::get(el);
    }

    template <CustomCureHealthAccessable T>
    static auto& get(const T& el) {
        return customAccessCureHealth<T>::get(el);
    }
};

}  // namespace traits
