#pragma once
#include "helper/same_as_ref.hpp"

struct Health;

template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), Health>;
};

template <typename T>
concept GetCureHealthAccessable = requires(T x) {
    x.getCureHealth();
    { x.getCureHealth() } -> same_as_ref<Health>;
};

namespace traits {

template <typename T>
struct CustomAccessCureHealth {};

template <typename T>
concept CustomCureHealthAccessable = requires(T x) {
    CustomAccessCureHealth<T>::get(x);
    { CustomAccessCureHealth<T>::get(x) } -> same_as_ref<Health>;
};

struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) {
        return el.cureHealth;
    }

    static auto& get(GetCureHealthAccessable auto& el) {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
    static auto& get(T& el) {
        return CustomAccessCureHealth<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
