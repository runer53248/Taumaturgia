#pragma once
#include "helper/same_as_ref.hpp"

struct Health;

template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getHp() } -> same_as_ref<Health>;
    { y.getHp() } -> same_as_ref<const Health>;
};

namespace traits {

template <typename T>
struct CustomAccessHealth {};

template <typename T>
concept CustomHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessHealth<T>::get(x) } -> same_as_ref<Health>;
    { CustomAccessHealth<T>::get(y) } -> same_as_ref<const Health>;
};

struct accessHealth {
    static auto& get(HealthAccessable auto& el) {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not CustomHealthAccessable<T>)  // use custom access if available
    static decltype(auto) get(T& el) {
        return el.getHp();
    }

    template <CustomHealthAccessable T>
    static decltype(auto) get(T& el) {
        return CustomAccessHealth<std::remove_cv_t<T>>::get(el);
    }

    template <CustomHealthAccessable T>
    static decltype(auto) get(const T& el) {
        return CustomAccessHealth<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
