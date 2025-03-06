#pragma once
#include "pipeing_result.hpp"

namespace impl {

template <typename T, typename... Props>
struct Creator {
    static_assert(
        helpers::all_properties_type_ordered<Props...> or helpers::none_properties_type_ordered<Props...>,
        "All properties must be of one type: ordered or unordered.");

    using result_type = pipeing_result<T, Props...>;

    constexpr auto operator()() const {
        static_assert(std::constructible_from<result_type>, "Creator can't create result_type from default C-tor!");
        return result_type{};
    }

    template <typename Arg, typename... Args>
    constexpr auto operator()(Arg&& arg, Args&&... args) const {
        constexpr bool arg_signals_unordered_args = std::is_same_v<std::remove_cvref_t<Arg>, decltype(unordered)>;

        if constexpr (arg_signals_unordered_args) {                              // token was introduced
            if constexpr (std::constructible_from<result_type, Arg, Args...>) {  // can be constructed with Arg
                return result_type(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else if constexpr (std::constructible_from<result_type, Args...>) {  // can be constructed without Arg
                return result_type(std::forward<Args>(args)...);
            } else {
                static_assert(false, "Creator with unordered args can't create result_type from given arguments!");
            }
        } else {  // token not introduced
            static_assert(std::constructible_from<result_type, Arg, Args...>, "Creator can't create result_type from given arguments!");
            return result_type(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    }
};

}  // namespace impl

namespace From {

template <typename T>
struct BaseType {};

template <typename T>
[[maybe_unused]] constexpr BaseType<T> base{};  // can be used even when T don't have default C-tor.

}  // namespace From

template <
    typename T,
    template <template <typename...> typename> typename P,
    template <typename...> typename Prop>
    requires is_property_type<P>
constexpr auto operator|(From::BaseType<T>, P<Prop>) -> impl::Creator<T, P<Prop>> {
    return {};
}

template <
    typename T,
    typename... Props,
    template <template <typename...> typename> typename P,
    template <typename...> typename Prop>
    requires is_property_type<P>
constexpr auto operator|(impl::Creator<T, Props...>, P<Prop>) -> impl::Creator<T, Props..., P<Prop>> {
    return {};
}
