#pragma once
#include "helper/same_as_ref.hpp"

template <typename T, typename TYPE>
concept UserTypeAccessable = requires(T x) {
    x.type;
    std::is_same_v<decltype(T::type), TYPE>;
};

template <typename T, typename TYPE>
concept GetUserTypeAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getType() } -> same_as_ref<TYPE>;
    { y.getType() } -> same_as_ref<const TYPE>;
};

namespace traits {

template <typename T, typename TYPE>
struct CustomAccessUserType {};

template <typename T, typename TYPE>
concept CustomUserTypeAccessable_impl = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessUserType<T, TYPE>::get(x) } -> same_as_ref<TYPE>;
    { CustomAccessUserType<T, TYPE>::get(y) } -> same_as_ref<const TYPE>;
};

template <typename T, typename TYPE>
concept CustomUserTypeAccessable = CustomUserTypeAccessable_impl<T, TYPE>;

template <typename TYPE>
struct accessUserType {
    static auto& get(UserTypeAccessable<TYPE> auto& el) {
        return el.type;
    }

    template <GetUserTypeAccessable<TYPE> T>
        requires(not CustomUserTypeAccessable<T, TYPE>) // prefer custom access getters
    static decltype(auto) get(T& el) {
        return el.getType();
    }

    template <CustomUserTypeAccessable<TYPE> T>
    static decltype(auto) get(T& el) {
        return CustomAccessUserType<std::remove_cv_t<T>, TYPE>::get(el);
    }

    template <CustomUserTypeAccessable<TYPE> T>
    static decltype(auto) get(const T& el) {
        return CustomAccessUserType<std::remove_cv_t<T>, TYPE>::get(el);
    }
};

}  // namespace traits
