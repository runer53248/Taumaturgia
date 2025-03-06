#pragma once
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

namespace With {

template <template <typename, typename...> typename P, typename... Tags>
struct ApplyTag {
    template <typename T>
    using apply = P<T, Tags...>;

    template <typename T>
    using apply_order = std::conditional_t<
        trait_accessable<T, typename P<T, Tags...>::hold_type>,
        T,
        P<T, Tags...>>;
};

// * forced version - will not be removed by taged versions - but be added even when trait in base is accessable
[[maybe_unused]] constexpr Property<Naming_impl> Name{};
[[maybe_unused]] constexpr Property<Damaging_impl> Damage{};
[[maybe_unused]] constexpr Property<Healing_impl> CureHealth{};
[[maybe_unused]] constexpr Property<Living_impl> Health{};
[[maybe_unused]] constexpr Property<Protecting_impl> Protection{};
[[maybe_unused]] constexpr Property<Restoring_impl> EffectTypeContainer{};
[[maybe_unused]] constexpr Property<Wearing_impl> WearContainer{};

// classic version - will be removed by taged versions
[[maybe_unused]] constexpr Property<Naming> Name_once{};
[[maybe_unused]] constexpr Property<Damaging> Damage_once{};
[[maybe_unused]] constexpr Property<Healing> CureHealth_once{};
[[maybe_unused]] constexpr Property<Living> Health_once{};
[[maybe_unused]] constexpr Property<Protecting> Protection_once{};
[[maybe_unused]] constexpr Property<Restoring> EffectTypeContainer_once{};
[[maybe_unused]] constexpr Property<Wearing> WearContainer_once{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property<P> property{};

template <template <typename, typename> typename P, typename... Tags>
[[maybe_unused]] constexpr Property<ApplyTag<P, Tags...>::template apply> taged_property{};

template <template <typename, typename> typename P, typename... Tags>
[[maybe_unused]] constexpr Property<ApplyTag<P, Tags...>::template apply_order> taged_property_once{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property<AdvanceUserProperty<T, Tags...>::template type> user_property{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property<AdvanceUserProperty<T, Tags...>::template order> user_property_once{};

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
