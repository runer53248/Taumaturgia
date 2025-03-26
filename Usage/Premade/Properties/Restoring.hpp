#pragma once
#include "Features.hpp"
#include "Implementation/Restoring.hpp"

namespace impl {

// MARK: Restoring_

template <typename T>
class Restoring_ : public Features_<RestoringSimple_<T>> {
public:
    using property_data = PropertyData<Restoring_, T>;
    using child = Features_<RestoringSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace impl::Test

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, impl::Restoring_<T>>;
