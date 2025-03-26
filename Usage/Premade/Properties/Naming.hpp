#pragma once
#include "Features.hpp"
#include "Implementation/Naming.hpp"

// #include "Usage/Traits/accessName.hpp"

namespace impl {

// MARK: Naming_

template <typename T>
class Naming_ : public Features_<NamingSimple_<T>> {
public:
    using property_data = PropertyData<Naming_, T>;
    using child = Features_<NamingSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace impl::Test

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
