#pragma once
#include "Features.hpp"
#include "Implementation/Protecting.hpp"

namespace impl {

// MARK: Protecting_

template <typename T>
class Protecting_ : public Features_<ProtectingSimple_<T>> {
public:
    using property_data = PropertyData<Protecting_, T>;
    using child = Features_<ProtectingSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace impl::Test

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, impl::Protecting_<T>>;
