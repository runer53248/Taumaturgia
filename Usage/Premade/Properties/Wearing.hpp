#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Wearing.hpp"

namespace impl {

template <typename T, typename... Tags>
class Wearing_ : public Features_<WearingSimple_<T, Tags...>> {
public:
    using property_data = PropertyData<For<Wearing_, Tags...>::template type, T, Tags...>;
    using child = Features_<WearingSimple_<T, Tags...>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
static_assert(Wearingable<Wearing_<tag>>);
}  // namespace impl::Test

template <typename T, typename... Tags>
using Wearing = apply_property<T, impl::Wearing_, Tags...>;
