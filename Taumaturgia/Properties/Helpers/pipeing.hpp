#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"  // for UserPropertyAdapter
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
struct HELP {
    constexpr HELP(T&& data) noexcept
        : data{std::forward<T>(data)} {}
    template <typename LL>
    constexpr HELP(HELP<T, LL>&& other) noexcept
        : data{std::forward<T>(other.data)} {}

    constexpr HELP() noexcept = delete;

    constexpr HELP(const HELP&) noexcept = default;
    constexpr HELP& operator=(const HELP&) noexcept = default;

    constexpr HELP(HELP&&) noexcept = default;
    constexpr HELP& operator=(HELP&&) noexcept = default;

    constexpr ~HELP() noexcept(std::is_nothrow_destructible_v<T>) = default;

    // use given base object to create new type object
    // template <typename TT, typename... PreProps>
    // friend auto operator|(impl::HELP<TT, list<PreProps...>>&& tp, decltype(Create));

    // template <typename TT, typename... PreProps, typename Prop>
    // friend auto operator|(impl::HELP<TT, list<PreProps...>>&& tp, Prop);

    // private:
    T data;
};

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

// return: taged_list<Prop1, Prop2>
template <
    template <template <typename...> typename> typename P1,
    template <typename...> typename Prop1,
    template <template <typename...> typename> typename P2,
    template <typename...> typename Prop2>
auto operator|(P1<Prop1>, P2<Prop2>) {
    if constexpr (std::same_as<taged_list<Prop1>, taged_list<Prop2>>) {
        return taged_list<Prop1>{};
    } else {
        using result = taged_list<Prop1, Prop2>;
        return result{};
    }
}

// return: taged_list<Props..., Prop2>
template <
    typename... Props,
    template <template <typename...> typename> typename P,
    template <typename> typename Prop2>
auto operator|(list<Props...>, P<Prop2>) {
    if constexpr (boost::mp11::mp_count<list<Props...>, Prop2<tag>>::value > 0) {
        return list<Props...>{};
    } else {
        return boost::mp11::mp_append<list<Props...>, taged_list<Prop2>>{};
    }
}

// use given base object to create new type object
template <typename T, typename... Props>
decltype(auto) operator|(impl::HELP<T, list<Props...>>&& tp, decltype(Create)) {
    return (add_properties<std::remove_cvref_t<T>, Props...>{std::forward<T>(tp.data)});
}
template <typename T, typename... Props>
decltype(auto) operator|(impl::HELP<T, list<Props...>>& tp, decltype(Create)) {
    return (add_properties<std::remove_cvref_t<T>, Props...>{std::forward<T>(tp.data)});
}
template <typename T, typename... Props>
decltype(auto) operator|(T&& tp, decltype(Create)) {
    return (tp);
}

// return: impl::HELP<T&&, list<Props...>>
template <typename T, typename... Props, typename Prop2>
decltype(auto) operator|(impl::HELP<T, list<Props...>>&& tp, Prop2) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop2::template apply<base_type>;
    if constexpr (std::is_same_v<
                      helper,
                      base_type>) {  // ignore unnecesary property for type T
        return (tp);
    } else {
        using prop_list = helpers::append_and_order_property_lists<list<Props...>, list<Prop2>>;
        if constexpr (std::same_as<
                          prop_list,
                          list<Props...>>) {  // skip if property list don't change
            return (tp);                      // one && less
        } else {
            return (impl::HELP<T, prop_list>{std::forward<T>(tp.data)});
        }
    }
}

// return: impl::HELP<T&&, list<Prop>> or T&&
template <typename T, typename Prop>
decltype(auto) operator|(T&& t, Prop) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop::template apply<base_type>;
    if constexpr (std::is_same_v<
                      helper,
                      base_type>) {  // ignore unnecesary property for type T
        return (t);
    } else {
        return (impl::HELP<T, list<Prop>>{std::forward<T>(t)});
    }
}

template <
    typename T,
    template <typename> typename... Props,
    typename P>
auto operator|(T&& t, list<Props<P>...>) {

    // using result = add_properties<std::remove_cvref_t<T>, Property<Props<P>::template apply>...>;
    using result = creator_add_properties<std::remove_cvref_t<T>, Props<P>::template apply...>;
    return result{std::forward<T>(t)};
}
