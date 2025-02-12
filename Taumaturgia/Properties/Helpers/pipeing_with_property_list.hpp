#pragma once

namespace impl {

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

template <typename T, typename... Props>
auto operator|(T&& t, list<Props...>) {
    return impl::pipe_helper(std::forward<T>(t), Props{}...);
}
