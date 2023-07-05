#pragma once
#include <type_traits>

struct Health;

template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(T x) {
    x.getHp();
    { x.getHp() } -> std::convertible_to<Health>;
};

namespace traits {

template <typename T>
struct customAccessHealth {};

template <typename T>
concept CustomHealthAccessable = requires(T x) {
    customAccessHealth<T>::get(x);
    { customAccessHealth<T>::get(x) } -> std::convertible_to<Health>;
};

struct accessHealth {
    static auto& get(HealthAccessable auto& el) {
        return el.hp;
    }

    static auto& get(GetHealthAccessable auto& el) {
        return el.getHp();
    }

    template <CustomHealthAccessable T>
    static auto& get(T& el) {
        return customAccessHealth<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
