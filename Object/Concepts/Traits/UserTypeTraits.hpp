#pragma once
#include "helper/same_as_ref.hpp"

template <typename T, typename TYPE>
concept GetAccessableType = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<TYPE>() } -> same_as_ref<TYPE>;
    { y.template getType<TYPE>() } -> same_as_ref<const TYPE>;
};

namespace traits {

template <typename TYPE, typename T>
struct CustomAccessType;  // {};

// CustomAccessType to replace all default 
// template <typename TYPE, typename T>
// struct traits::CustomAccessType {
//     static decltype(auto) get(GetAccessableSpecificType<TYPE> auto& el) {
//         return el.template getType<TYPE>();
//     }
// };

template <typename T, typename TYPE>
concept CustomAccessableType_impl = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessType<TYPE, T>::get(x) } -> same_as_ref<TYPE>;
    { CustomAccessType<TYPE, T>::get(y) } -> same_as_ref<const TYPE>;
};

template <typename T, typename TYPE>
concept CustomAccessableType = CustomAccessableType_impl<T, TYPE>;

template <typename TYPE>
struct accessType {
    template <GetAccessableType<TYPE> T>
        requires(not CustomAccessableType<T, TYPE>)  // prefer custom access getters
    static decltype(auto) get(T& el) {
        return el.template getType<TYPE>();
    }

    template <CustomAccessableType<TYPE> T>
    static decltype(auto) get(T& el) {
        return CustomAccessType<TYPE, std::remove_cv_t<T>>::get(el);
    }

    template <CustomAccessableType<TYPE> T>
    static decltype(auto) get(const T& el) {
        return CustomAccessType<TYPE, std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
