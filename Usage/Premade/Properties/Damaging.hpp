#pragma once
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Damaging.hpp"

namespace impl {

template <typename T, typename... Tags>
class Damaging_;

template <typename... Tags>
struct Damaging_For {
    template <typename TARGET>
    using type = Damaging_<TARGET, Tags...>;
};

template <typename T, typename... Tags>
class Damaging_ : public Features_<DamagingSimple_<T, Tags...>> {
public:
    using property_data = PropertyData<Damaging_For<Tags...>::template type, T, Tags...>;
    using child = Features_<DamagingSimple_<T, Tags...>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);
static_assert(Damagingable<Damaging_<tag>>);
}  // namespace impl::Test

template <typename T, typename... Tags>
using Damaging = apply_property<T, impl::Damaging_, Tags...>;
