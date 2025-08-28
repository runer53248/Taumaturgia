#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Restoring.hpp"

namespace impl {

// MARK: Restoring_

template <typename T, typename... Tags>
class Restoring_ : public Features_<RestoringSimple_<T, Tags...>> {
public:
    using property_data = PropertyData<For<Restoring_, Tags...>::template type, T, Tags...>;
    using base = Features_<RestoringSimple_<T, Tags...>>;
    using typename base::hold_type;

    using base::base;
};

}  // namespace impl

namespace impl::Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace impl::Test

template <typename T, typename... Tags>
using Restoring = apply_property<T, impl::Restoring_, Tags...>;
