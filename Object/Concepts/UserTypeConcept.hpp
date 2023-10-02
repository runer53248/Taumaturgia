#pragma once
#include <type_traits>
#include "Traits/UserTypeTraits.hpp"

template <typename T, typename TYPE>
concept UserTypeConceptable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessUserType<TYPE>::get(x) } -> same_as_ref<TYPE>;
    { traits::accessUserType<TYPE>::get(y) } -> same_as_ref<const TYPE>;
};
