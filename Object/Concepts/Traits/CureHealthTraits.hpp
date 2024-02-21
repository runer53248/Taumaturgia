#pragma once
#include "helper/same_as_ref.hpp"

struct CureHealth;

namespace traits {

template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), CureHealth>;
};

template <typename T>
concept GetCureHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getCureHealth() } -> same_as_ref<CureHealth>;
    { y.getCureHealth() } -> same_as_ref<const CureHealth>;
};

template <typename T>
struct CustomAccessCureHealth {};

template <typename T>
concept CustomCureHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessCureHealth<T>::get(x) } -> same_as_ref<CureHealth>;
    { CustomAccessCureHealth<T>::get(y) } -> same_as_ref<const CureHealth>;
};

template <typename T>
concept UserTypeCureHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<CureHealth>() } -> same_as_ref<CureHealth>;
    { y.template getType<CureHealth>() } -> same_as_ref<const CureHealth>;
};

struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not CustomCureHealthAccessable<T> and not UserTypeCureHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not UserTypeCureHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessCureHealth<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeCureHealthAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<CureHealth>();
    }
};

}  // namespace traits
