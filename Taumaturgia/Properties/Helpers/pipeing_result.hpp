#pragma once

namespace impl {

template <typename T, typename... Props>
using pipeing_result = add_properties<
    std::remove_cvref_t<T>,
    std::conditional_t<
        std::same_as<typename Props::tags_list, list<>> and
            trait_accessable<std::remove_cvref_t<T>, typename Props::hold_type>,                   // check if base have accessable hold_type trait
        typename Props::template property_type<UserPropertyAdapter<::empty_type>::template type>,  // property of empty_type that will be autoremoved
        Props>...>;

}  // namespace impl
