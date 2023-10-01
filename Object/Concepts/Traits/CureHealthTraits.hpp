#pragma once
#include "helper/same_as_ref.hpp"

struct Health;

template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), Health>;
};

template <typename T>
concept GetCureHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getCureHealth() } -> same_as_ref<Health>;
    { y.getCureHealth() } -> same_as_ref<const Health>;
};

namespace traits {

template <typename T>
struct CustomAccessCureHealth {};

template <typename T>
concept CustomCureHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessCureHealth<T>::get(x) } -> same_as_ref<Health>;
    { CustomAccessCureHealth<T>::get(y) } -> same_as_ref<const Health>;
};

struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
    requires (not CustomCureHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
    static decltype(auto) get(T& el) {
        return CustomAccessCureHealth<std::remove_cv_t<T>>::get(el);
    }

    template <CustomCureHealthAccessable T>
    static decltype(auto) get(const T& el) {
        return CustomAccessCureHealth<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
