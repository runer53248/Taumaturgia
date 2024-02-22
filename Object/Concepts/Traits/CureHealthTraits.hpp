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
concept GetCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getCureHealth() } -> same_as_ref<CureHealth>;
    { std::as_const(x).getCureHealth() } -> same_as_ref<const CureHealth>;
};

template <typename T>
struct CustomAccessCureHealth {};

template <typename T>
concept CustomCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessCureHealth<T>::get(x) } -> same_as_ref<CureHealth>;
    { CustomAccessCureHealth<T>::get(std::as_const(x)) } -> same_as_ref<const CureHealth>;
};

template <typename T>
concept UserTypeCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<CureHealth>() } -> same_as_ref<CureHealth>;
    { std::as_const(x).template getType<CureHealth>() } -> same_as_ref<const CureHealth>;
};

struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or UserTypeCureHealthAccessable<T>))
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
