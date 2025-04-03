#pragma once
#include "Constructors.hpp"
#include "Features.hpp"
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
using Living = std::conditional_t<Livingable<T>, T, impl::Living_<T>>;
