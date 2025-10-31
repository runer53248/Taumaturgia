#pragma once
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

namespace impl {

template <template <typename, typename...> typename P, typename... Tags>
    requires(not std::same_as<
             P<P<tag, Tags...>, Tags...>,
             P<tag, Tags...>>)  // is_property_forced
struct ApplyTag {
private:
    template <typename T>
    using hold_type = typename P<T, Tags...>::hold_type;

public:
    template <typename T>
    using apply = P<T, Tags...>;
};

}  // namespace impl

namespace With {

// * forced version - will not be removed by taged versions - but be added even when trait in base is accessable
[[maybe_unused]] constexpr Property_ordered<Naming_impl> Name{};
[[maybe_unused]] constexpr Property_ordered<Damaging_impl> Damage{};
[[maybe_unused]] constexpr Property_ordered<Healing_impl> CureHealth{};
[[maybe_unused]] constexpr Property_ordered<Living_impl> Health{};
[[maybe_unused]] constexpr Property_ordered<Protecting_impl> Protection{};
[[maybe_unused]] constexpr Property_ordered<Restoring_impl> EffectTypeContainer{};
[[maybe_unused]] constexpr Property_ordered<Wearing_impl> WearContainer{};

// classic version - will be removed by taged versions
[[maybe_unused]] constexpr Property_ordered<Naming> Name_once{};
[[maybe_unused]] constexpr Property_ordered<Damaging> Damage_once{};
[[maybe_unused]] constexpr Property_ordered<Healing> CureHealth_once{};
[[maybe_unused]] constexpr Property_ordered<Living> Health_once{};
[[maybe_unused]] constexpr Property_ordered<Protecting> Protection_once{};
[[maybe_unused]] constexpr Property_ordered<Restoring> EffectTypeContainer_once{};
[[maybe_unused]] constexpr Property_ordered<Wearing> WearContainer_once{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property_ordered<P> property{};

template <template <typename, typename> typename P, typename... Tags>
[[maybe_unused]] constexpr Property_ordered<impl::ApplyTag<P, Tags...>::template apply> taged_property{};

// template <template <typename, typename> typename P, typename... Tags>
// [[maybe_unused]] constexpr Property_ordered<impl::ApplyTag<P, Tags...>::template apply_order> taged_property_once{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property_ordered<UserPropertyAdapter<T, Tags...>::template apply> user_property{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property_ordered<UserPropertyAdapter<T, Tags...>::template once> user_property_once{};

namespace impl {

template <typename TT>
struct t_help;

template <template <typename...> typename TT,
          typename TType,
          typename... TTags>
struct t_help<TT<TType, TTags...>> {
    template <typename T>
    using type = UserPropertyAdapter<TType, TTags...>::template apply<T>;
};

}  // namespace impl

template <typename TT>
[[maybe_unused]] constexpr Property_ordered<impl::t_help<TT>::template type> user_property_t{};

};  // namespace With

namespace WithUnordered {
[[maybe_unused]] constexpr Property_unordered<Naming_impl> Name{};
[[maybe_unused]] constexpr Property_unordered<Damaging_impl> Damage{};
[[maybe_unused]] constexpr Property_unordered<Healing_impl> CureHealth{};
[[maybe_unused]] constexpr Property_unordered<Living_impl> Health{};
[[maybe_unused]] constexpr Property_unordered<Protecting_impl> Protection{};
[[maybe_unused]] constexpr Property_unordered<Restoring_impl> EffectTypeContainer{};
[[maybe_unused]] constexpr Property_unordered<Wearing_impl> WearContainer{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property_unordered<P> property{};

template <template <typename, typename> typename P, typename... Tags>
[[maybe_unused]] constexpr Property_unordered<impl::ApplyTag<P, Tags...>::template apply> taged_property{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property_unordered<UserPropertyAdapter<T, Tags...>::template apply> user_property{};

template <typename T, typename... Tags>
[[maybe_unused]] constexpr Property_unordered<UserPropertyAdapter<T, Tags...>::template once> user_property_once{};

};  // namespace WithUnordered
