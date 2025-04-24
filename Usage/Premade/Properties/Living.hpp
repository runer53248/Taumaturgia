#pragma once
#include "Helpers/Constructors.hpp"
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Living.hpp"

namespace impl {

template <typename T>
class Living_ : public Features_<Constructors_<LivingSimple_<T>>> {
public:
    using property_data = PropertyData<Living_, T>;
    using child = Features_<Constructors_<LivingSimple_<T>>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);
}  // namespace impl::Test

template <typename T>
using Living = apply_property<T, impl::Living_>;
