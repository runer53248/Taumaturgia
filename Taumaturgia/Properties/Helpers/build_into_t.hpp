#pragma once
#include <boost/mp11.hpp>

namespace helpers::impl {
template <typename Base, typename L>
struct build_into_impl {
private:
    using first = boost::mp11::mp_first<L>;
    using rest = boost::mp11::mp_rest<L>;

public:
    using type = first::template apply<typename build_into_impl<Base, rest>::type>;
};

template <typename Base, typename L>
    requires boost::mp11::mp_empty<L>::value
struct build_into_impl<Base, L> {
    using type = Base;
};
}  // namespace helpers::impl

namespace helpers {
template <typename Base, typename L>
using build_into_t = impl::build_into_impl<Base, L>::type;
}  // namespace helpers
