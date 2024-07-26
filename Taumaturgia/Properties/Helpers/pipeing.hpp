#pragma once
#include "taged_list.hpp"

namespace impl {

template <typename T, template <typename> typename Prop>
auto creator_impl() {
    return []<typename Arg, typename... Args>(Arg&& arg, Args&&... args) {
        constexpr bool inv_first_arg = std::invocable<T, Arg>;
        constexpr bool token_same = std::is_same_v<std::remove_cvref_t<Arg>, Token>;

        if constexpr (inv_first_arg) {
            using type = std::invoke_result_t<T, Arg>;
            using result_property = add_properties<type, Prop>;

            if constexpr (not token_same) {  // token not introduced
                static_assert(std::constructible_from<result_property, Arg, Args...>);
                return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else {                                                                     // token was introduced
                if constexpr (std::constructible_from<result_property, Arg, Args...>) {  // can be constructed
                    static_assert(std::constructible_from<result_property, Arg, Args...>);
                    return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
                } else if constexpr (std::constructible_from<result_property, Args...>) {  // ignore token Arg
                    static_assert(std::constructible_from<result_property, Args...>);
                    return result_property(std::forward<Args>(args)...);
                } else {  // T is base type (propably) and token was introduced - meaning unknown order of arguments given
                    auto result = result_property{};
                    ((trait<Args>::get(result) = std::forward<Args>(args)), ...);
                    return result;
                }
            }
        } else if constexpr (token_same) {  // token was introduced
            using type = T;
            using result_property = add_properties<type, Prop>;

            if constexpr (std::constructible_from<result_property, Arg, Args...>) {
                static_assert(std::constructible_from<result_property, Arg, Args...>);
                return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else {  // ignore Arg == Token
                static_assert(std::constructible_from<result_property, Args...>);
                return result_property(std::forward<Args>(args)...);
            }
        } else {  // token not introduced
            using type = T;
            using result_property = add_properties<type, Prop>;

            static_assert(std::constructible_from<result_property, Arg, Args...>);
            return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    };
}

}  // namespace impl

template <typename T, template <typename> typename Prop>
auto operator|(T, Property<Prop>) {
    return impl::creator_impl<T, Prop>();
}

// return: taged_list<Prop1, Prop2>
template <template <typename...> typename Prop1, template <typename...> typename Prop2>
auto operator|(Property<Prop1>, Property<Prop2>) {
    return taged_list<Prop1, Prop2>{};
}

// return: taged_list<Props..., Prop2>
template <typename... Props, template <typename> typename Prop2>
auto operator|(list<Props...>, Property<Prop2>) {
    return boost::mp11::mp_append<list<Props...>, taged_list<Prop2>>{};
}

// for build in properties
template <typename T, template <typename> typename... Props, typename P>
auto fx([[maybe_unused]] T&& t, Props<P>...) {
    using result = add_properties<T, Props<P>::template apply...>;
    if constexpr (std::same_as<std::remove_cvref_t<T>, result>) {
        return t;
    } else {
        return result{t};
    }
}

#include "Taumaturgia/Properties/UserProperty.hpp"  // for UserPropertyAdapter

// for user type properties
template <typename T, template <typename, typename> typename... Props, typename... TYPES, typename P>
auto fx(T t, Props<TYPES, P>...) {
    using result = add_properties<T, UserPropertyAdapter<TYPES>::template type...>;
    return result(t);
}

//
template <typename T, typename... Props>
auto operator|(T&& t, list<Props...>) {
    return fx(std::forward<T>(t), Props{}...);
}
