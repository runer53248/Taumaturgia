#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Protecting.hpp"

namespace impl {

template <typename T>
class Protecting_ : public Features_<ProtectingSimple_<T>> {
public:
    using property_data = PropertyData<Protecting_, T>;
    using base = Features_<ProtectingSimple_<T>>;
    using typename base::hold_type;

    using base::base;
};

}  // namespace impl

namespace impl::Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace impl::Test

template <typename T>
using Protecting = apply_property<T, impl::Protecting_>;
