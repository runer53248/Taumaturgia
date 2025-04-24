#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Wearing.hpp"

namespace impl {

template <typename T>
class Wearing_ : public Features_<WearingSimple_<T>> {
public:
    using property_data = PropertyData<Wearing_, T>;
    using child = Features_<WearingSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
}  // namespace impl::Test

template <typename T>
using Wearing = apply_property<T, impl::Wearing_>;
