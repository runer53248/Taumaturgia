#pragma once
#include <type_traits>

template <typename T, template <typename...> typename PropImpl, typename... Tags>
using apply_property = std::conditional_t<
    trait_accessable<T, typename PropImpl<T, Tags...>::hold_type>,
    T,
    PropImpl<T, Tags...>>;
