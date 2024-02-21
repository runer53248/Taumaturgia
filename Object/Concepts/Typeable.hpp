#pragma once
#include <type_traits>
#include "Traits/UserTypeTraits.hpp"

template <typename T, typename RESULT_TYPE>
concept Typeable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessType<RESULT_TYPE>::get(x) } -> same_as_ref<RESULT_TYPE>;
    { traits::accessType<RESULT_TYPE>::get(y) } -> same_as_ref<const RESULT_TYPE>;
};

template <typename T, typename RESULT_TYPE>
concept GetTypeable = traits::GetTypeAccessable<T, RESULT_TYPE>;
