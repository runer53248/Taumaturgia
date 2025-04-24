#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Naming.hpp"

namespace impl {

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
using Naming = apply_property<T, impl::Naming_>;
