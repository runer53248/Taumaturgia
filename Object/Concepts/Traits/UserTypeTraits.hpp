#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

namespace traits {

template <typename T, typename TYPE>
concept GetTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE>() } -> same_as_ref<TYPE>;
    { std::as_const(x).template getType<TYPE>() } -> same_as_ref<const TYPE>;
};

template <typename TYPE, typename T>
struct CustomAccessType;

template <typename T, typename TYPE>
concept CustomTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(x) } -> same_as_ref<TYPE>;
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(std::as_const(x)) } -> same_as_ref<const TYPE>;
};

template <typename TYPE>
struct accessType {
    template <GetTypeAccessable<TYPE> T>
        requires(not CustomTypeAccessable<T, TYPE>)  // prefer custom access getters
    static decltype(auto) get(T& el) {
        return el.template getType<TYPE>();
    }

    template <CustomTypeAccessable<TYPE> T>
        requires(not GetTypeAccessable<TYPE, T>)
    static decltype(auto) get(T& el) {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }
};

}  // namespace traits
