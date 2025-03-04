#pragma once
#include "accessType.hpp"

template <typename T>
struct trait_ {
    using type = traits::impl::accessType<T>;
};

template <typename T>
using trait = trait_<T>::type;

template <typename T, typename ACCESSED_TYPE>
concept trait_accessable = trait<ACCESSED_TYPE>::template accessable<T>;
