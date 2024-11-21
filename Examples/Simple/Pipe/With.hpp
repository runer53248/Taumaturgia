#pragma once
#include "Usage/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

namespace With {
[[maybe_unused]] constexpr Property<Naming> Name{};
[[maybe_unused]] constexpr Property<Damaging> Damage{};
[[maybe_unused]] constexpr Property<Healing> CureHealth{};
[[maybe_unused]] constexpr Property<Living> Health{};
[[maybe_unused]] constexpr Property<Protecting> Protection{};
[[maybe_unused]] constexpr Property<Restoring> EffectTypeContainer{};
[[maybe_unused]] constexpr Property<Wearing> WearContainer{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property<P> property{};
template <typename T>
[[maybe_unused]] constexpr Property<UserPropertyAdapter<T>::template type> user_property{};
};  // namespace With
