#pragma once
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

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
template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property<AdvanceUserProperty<T, Tags...>::template type> user_property{};
template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property<AdvanceUserProperty<T, Tags...>::template order> user_property_order{};

namespace impl {

template <typename TT>
struct t_help;
template <template <typename, typename...> typename TT,
          typename TType,
          typename... TTags>
struct t_help<TT<TType, TTags...>> {
    template <typename T>
    using type = AdvanceUserProperty<TType, TTags...>::template type<T>;
};

}  // namespace impl

template <typename TT>
[[maybe_unused]] constexpr Property<impl::t_help<TT>::template type> user_property_t{};

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
template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property_unordered<UserPropertyAdapter<T, Tags...>::template type> user_property{};
};  // namespace WithUnordered
