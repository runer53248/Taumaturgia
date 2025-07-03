#pragma once
#include <type_traits>

template <template <typename...> typename PropImpl, typename... Tags>
concept is_property_forced = not std::same_as<
    PropImpl<PropImpl<tag, Tags...>, Tags...>,
    PropImpl<tag, Tags...>>;

template <typename T, template <typename...> typename PropImpl, typename... Tags>
struct apply_property_impl {
    static_assert(is_property_forced<PropImpl, Tags...>);

    using type = std::conditional_t<
        (trait_accessable<T, typename PropImpl<T, Tags...>::hold_type> and  //
         (is_getTypeTags_valid<T, typename PropImpl<T, Tags...>::hold_type, Tags...>)),
        T,
        PropImpl<T, Tags...>>;
};

template <typename T, template <typename...> typename PropImpl, typename... Tags>
using apply_property = apply_property_impl<T, PropImpl, Tags...>::type;
