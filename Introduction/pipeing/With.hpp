#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Usage/Properties.hpp"

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

namespace WithUnordered {
[[maybe_unused]] constexpr Property_unordered<Naming> Name{};
[[maybe_unused]] constexpr Property_unordered<Damaging> Damage{};
[[maybe_unused]] constexpr Property_unordered<Healing> CureHealth{};
[[maybe_unused]] constexpr Property_unordered<Living> Health{};
[[maybe_unused]] constexpr Property_unordered<Protecting> Protection{};
[[maybe_unused]] constexpr Property_unordered<Restoring> EffectTypeContainer{};
[[maybe_unused]] constexpr Property_unordered<Wearing> WearContainer{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property_unordered<P> property{};
template <typename T>
[[maybe_unused]] constexpr Property_unordered<UserPropertyAdapter<T>::template type> user_property{};
};  // namespace WithUnordered
