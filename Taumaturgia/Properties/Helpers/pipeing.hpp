#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"  // for UserPropertyAdapter
#include "taged_list.hpp"

template <typename T, template <typename...> typename... properties>
#ifndef IGNORE_ORDER_LIST
using creator_add_properties = add_properties<T, properties...>;
#else
using creator_add_properties = add_properties_unordered<T, properties...>;
#endif

namespace impl {

template <typename T>
struct Creator {
    using result_type = T;

    auto operator()() const {
        static_assert(std::constructible_from<result_type>, "Creator can't create result_type from default C-tor!");
        return result_type{};
    }

    template <typename Arg, typename... Args>
    auto operator()(Arg&& arg, Args&&... args) const {
        constexpr bool token_introduced = std::is_same_v<std::remove_cvref_t<Arg>, Token>;

        if constexpr (token_introduced) {                                        // token was introduced
            if constexpr (std::constructible_from<result_type, Arg, Args...>) {  // can be constructed
                return result_type(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else if constexpr (std::constructible_from<result_type, Args...>) {  // can be constructed, ignore Arg == Token
                return result_type(std::forward<Args>(args)...);
            } else {
                static_assert(false, "Creator with token introduced can't create result_type from given arguments!");
            }
        } else {  // token not introduced
            static_assert(std::constructible_from<result_type, Arg, Args...>, "Creator can't create result_type from given arguments!");
            return result_type(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    }
};

// for build in properties
template <typename T, template <typename> typename... Props, typename P>
auto pipe_helper(T&& t, Props<P>...) {
    using result = ::creator_add_properties<std::remove_cvref_t<T>, Props<P>::template apply...>;

    return result{std::forward<T>(t)};
}

// for user type properties
template <typename T, template <typename, typename> typename... Props, typename... TYPES, typename P>
auto pipe_helper(T&& t, Props<TYPES, P>...) {
    using result = ::creator_add_properties<std::remove_cvref_t<T>, UserPropertyAdapter<TYPES>::template type...>;

    return result{std::forward<T>(t)};
}

}  // namespace impl

template <typename T>
struct BaseType {};

namespace From {
template <typename T>
[[maybe_unused]] constexpr BaseType<T> base{};  // can be used even when T don't have default C-tor.
}  // namespace From

template <typename T, template <typename> typename Prop>
auto operator|(BaseType<T>, Property<Prop>) -> impl::Creator<::creator_add_properties<T, Prop>> {
    return {};
}

template <typename T, template <typename> typename Prop>
auto operator|(impl::Creator<T>, Property<Prop>) -> impl::Creator<::creator_add_properties<T, Prop>> {
    return {};
}

// return: taged_list<Prop1, Prop2>
template <template <typename...> typename Prop1, template <typename...> typename Prop2>
auto operator|(Property<Prop1>, Property<Prop2>) -> taged_list<Prop1, Prop2> {
    return {};
}

// return: taged_list<Props..., Prop2>
template <typename... Props, template <typename> typename Prop2>
auto operator|(list<Props...>, Property<Prop2>) -> boost::mp11::mp_append<list<Props...>, taged_list<Prop2>> {
    return {};
}

template <typename T, typename... Props>
auto operator|(T&& t, list<Props...>) {
    return impl::pipe_helper(std::forward<T>(t), Props{}...);
}
