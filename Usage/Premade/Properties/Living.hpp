#pragma once
#include "Helpers/Constructors.hpp"
#include "Helpers/Features.hpp"
#include "Helpers/apply_property.hpp"
#include "Implementation/Living.hpp"

namespace impl {

// MARK: Living_

template <typename T, typename... Tags>
class Living_ : public Features_<Constructors_<LivingSimple_<T, Tags...>>> {
public:
    using property_data = PropertyData<For<Living_, Tags...>::template type, T, Tags...>;
    using child = Features_<Constructors_<LivingSimple_<T, Tags...>>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);
}  // namespace impl::Test

template <typename T, typename... Tags>
using Living = apply_property<T, impl::Living_, Tags...>;
