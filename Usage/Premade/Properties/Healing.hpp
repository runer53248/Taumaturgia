#pragma once
#include "Helpers/Constructors.hpp"
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Healing.hpp"

namespace impl {

template <typename T>
class Healing_ : public Features_<Constructors_<HealingSimple_<T>>> {
public:
    using property_data = PropertyData<Healing_, T>;
    using child = Features_<Constructors_<HealingSimple_<T>>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Healing_Test {};
static_assert(Healingable<Healing_<Healing_Test>>);
}  // namespace impl::Test

template <typename T>
using Healing = apply_property<T, impl::Healing_>;
