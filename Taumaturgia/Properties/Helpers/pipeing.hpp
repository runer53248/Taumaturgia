#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"  // for UserPropertyAdapter
#include "Usage/Properties.hpp"
#include "taged_list.hpp"

#ifdef IGNORE_ORDER_LIST
constexpr bool with_ignore_order_list = true;
#else
constexpr bool with_ignore_order_list = false;
#endif

template <typename T, template <typename...> typename... properties>
using creator_add_properties = std::conditional_t<
    with_ignore_order_list,
    add_properties_ordered<T, properties...>,
    add_properties_unordered<T, properties...>>;

struct {
} Create;

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

template <typename T, typename L>
struct DataAndPropertiesList {
    constexpr DataAndPropertiesList(T&& data) noexcept
        : data{std::forward<T>(data)} {}

    template <typename LL>
    constexpr DataAndPropertiesList(DataAndPropertiesList<T, LL>&& other) noexcept
        : data{std::forward<T>(other.data)} {}

    T data;
};

// for build in properties
template <typename T, template <typename> typename... Props, typename P>
auto pipe_helper(T&& t, Props<P>...) {
    // using result = add_properties<std::remove_cvref_t<T>, Property<Props<tag>::template apply>...>;
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

template <
    typename T,
    template <template <typename...> typename> typename P,
    template <typename...> typename Prop>
    requires is_property_type<P>
auto operator|(BaseType<T>, P<Prop>) -> impl::Creator<::add_properties<T, P<Prop>>> {
    return {};
}

template <
    typename T,
    template <template <typename...> typename> typename P,
    template <typename...> typename Prop>
    requires is_property_type<P>
auto operator|(impl::Creator<T>, P<Prop>) -> impl::Creator<::add_properties<T, P<Prop>>> {
    return {};
}

template <
    template <template <typename...> typename> typename P1,
    template <typename...> typename Prop1,
    template <template <typename...> typename> typename P2,
    template <typename...> typename Prop2>
auto operator|(P1<Prop1>, P2<Prop2>) {
    if constexpr (std::same_as<taged_list<Prop1>, taged_list<Prop2>>) {
        return taged_list<Prop1>{};
    } else {
        return taged_list<Prop1, Prop2>{};
    }
}

template <
    typename... Props,
    template <template <typename...> typename> typename P,
    template <typename> typename Prop2>
auto operator|(list<Props...>, P<Prop2>) {
    using namespace boost::mp11;
    if constexpr (mp_contains<list<Props...>, Prop2<tag>>::value) {
        return list<Props...>{};
    } else {
        return mp_append<list<Props...>, taged_list<Prop2>>{};
    }
}

// Create new type object from DataAndPropertiesList
template <typename T, typename... Props>
decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>&& tp, decltype(Create)) {
    using namespace boost::mp11;
    static_assert(
        mp_count<list<mp_bool<helpers::impl::property_type_ordered<Props>::value>...>, mp_true>::value == sizeof...(Props)  //
        or
        mp_count<list<mp_bool<helpers::impl::property_type_ordered<Props>::value>...>, mp_false>::value == sizeof...(Props));
    return (add_properties<std::remove_cvref_t<T>, Props...>{std::forward<T>(tp.data)});
}
template <typename T, typename... Props>
decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>& tp, decltype(Create)) {
    using namespace boost::mp11;
    static_assert(
        mp_count<list<mp_bool<helpers::impl::property_type_ordered<Props>::value>...>, mp_true>::value == sizeof...(Props) or
        mp_count<list<mp_bool<helpers::impl::property_type_ordered<Props>::value>...>, mp_false>::value == sizeof...(Props));
    return (add_properties<std::remove_cvref_t<T>, Props...>{std::forward<T>(tp.data)});
}
// pipe when T isn't DataAndPropertiesList type
template <typename T, typename...>
decltype(auto) operator|(T&& tp, decltype(Create)) {
    return (tp);
}

template <typename T, typename... Props, typename Prop2>
decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>&& tp, Prop2) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop2::template apply<base_type>;
    if constexpr (std::is_same_v<helper, base_type>) {  // ignore unnecesary property for type T
        return (tp);
    } else {
        using namespace boost::mp11;
        using prop_list = helpers::append_and_order_property_lists<list<Props...>, list<Prop2>>;
        if constexpr (mp_contains<list<Props...>, Prop2>::value) {  // skip if property list contain Prop2
            return (tp);
        } else if constexpr (std::same_as<prop_list, list<Props...>>) {  // skip if property list don't change
            return (tp);
        } else {
            using prop_list = helpers::append_and_order_property_lists<list<Props...>, list<Prop2>>;
            return (impl::DataAndPropertiesList<T, prop_list>{std::forward<T>(tp.data)});
        }
    }
}

template <typename T, typename Prop>
    requires requires {
        typename Prop::template apply<std::remove_cvref_t<T>>;
    }
decltype(auto) operator|(T&& t, Prop) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop::template apply<base_type>;
    if constexpr (std::is_same_v<helper, base_type>) {  // ignore unnecessary property for type T
        return (t);
    } else {
        return (impl::DataAndPropertiesList<T, list<Prop>>{std::forward<T>(t)});
    }
}

template <typename T, typename... Props>
auto operator|(T&& t, list<Props...>) {
    return impl::pipe_helper(std::forward<T>(t), Props{}...);
}
