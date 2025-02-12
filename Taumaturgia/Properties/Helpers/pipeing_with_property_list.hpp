#pragma once

namespace impl {

template <typename T, typename... Props>
auto pipe_helper(T&& t, Props...) {
    using result = add_properties<std::remove_cvref_t<T>, Props...>;
    return result(std::forward<T>(t));
}

}  // namespace impl

// create list from two properties
template <
    template <template <typename...> typename> typename P,
    template <typename...> typename Prop1,
    template <typename...> typename Prop2>
auto operator|(P<Prop1>, P<Prop2>) {
    if constexpr (std::same_as<list<P<Prop1>>, list<P<Prop2>>>) {
        return list<P<Prop1>>{};
    } else {
        return list<P<Prop1>, P<Prop2>>{};
    }
}

// add property to list
template <
    typename... Props,
    template <template <typename...> typename> typename P,
    template <typename> typename Prop2>
auto operator|(list<Props...>, P<Prop2>) {
    using namespace boost::mp11;
    if constexpr (mp_contains<list<Props...>, P<Prop2>>::value) {
        return list<Props...>{};
    } else {
        return mp_append<list<Props...>, list<P<Prop2>>>{};
    }
}

// use property list on base
template <typename T, typename... Props>
auto operator|(T&& t, list<Props...>) {
    return impl::pipe_helper(std::forward<T>(t), Props{}...);
}
