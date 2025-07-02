#pragma once
#include <type_traits>

template <typename T, template <typename...> typename PropImpl, typename... Tags>
using apply_property = std::conditional_t<
    (trait_accessable<T, typename PropImpl<T, Tags...>::hold_type> and  //
     (is_getTypeTags_valid<T, typename PropImpl<T, Tags...>::hold_type, Tags...>)),
    T,
    PropImpl<T, Tags...>>;
