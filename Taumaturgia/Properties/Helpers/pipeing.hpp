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
    auto operator()() {
        static_assert(std::constructible_from<T>);
        return T{};
    }

    template <typename Arg, typename... Args>
    auto operator()(Arg&& arg, Args&&... args) {
        constexpr bool token_introduced = std::is_same_v<std::remove_cvref_t<Arg>, Token>;
        
        if constexpr (token_introduced) {  // token was introduced
            using result_property = T;

            if constexpr (std::constructible_from<result_property, Arg, Args...>) {  // can be constructed
                static_assert(std::constructible_from<result_property, Arg, Args...>);
                return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else {  // can be constructed, ignore Arg == Token
                static_assert(std::constructible_from<result_property, Args...>);
                return result_property(std::forward<Args>(args)...);
            }
        } else {  // token not introduced
            using result_property = T;

            static_assert(std::constructible_from<result_property, Arg, Args...>);
            return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    }
};

// for build in properties
template <typename T, template <typename> typename... Props, typename P>
auto pipe_helper(T&& t, Props<P>...) {
    using result = ::creator_add_properties<std::remove_cvref_t<T>, Props<P>::template apply...>;

    if constexpr (std::same_as<std::remove_cvref_t<T>, result>) {
        return std::forward<T>(t);
    } else {
        return result{std::forward<T>(t)};
    }
}

// for user type properties
template <typename T, template <typename, typename> typename... Props, typename... TYPES, typename P>
auto pipe_helper(T&& t, Props<TYPES, P>...) {
    using result = ::creator_add_properties<std::remove_cvref_t<T>, UserPropertyAdapter<TYPES>::template type...>;

    return result{std::forward<T>(t)};
}

}  // namespace impl

template <typename T, template <typename> typename Prop>
auto operator|(T, Property<Prop>) -> impl::Creator<::creator_add_properties<T, Prop>> {
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
