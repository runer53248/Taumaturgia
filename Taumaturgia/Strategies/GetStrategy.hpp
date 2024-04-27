#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Traits/DamageTraits.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"
#include "Taumaturgia/Traits/ProtectionTraits.hpp"
#include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"
#include "Taumaturgia/Types/VariantType.hpp"

enum class Properties;

template <typename T>
struct GetStrategy_ {};

template <typename T>
concept Gettingable = Damagingable<T> or Healingable<T> or Livingable<T> or Protectingable<T> or Restoringable<T> or Wearingable<T>;

template <typename T>
using GetStrategy = std::conditional_t<
    Gettingable<T>,
    std::conditional_t<
        Strategable_template<GetStrategy_, T, optional_get_variant_type, Properties>  //
            and Strategable_template<GetStrategy_, const T, optional_get_variant_const_type, Properties>,
        GetStrategy_<T>,
        GetStrategy_<Default>>,
    GetStrategy_<T>>;

template <typename T>
concept is_get_strategy = Strategable_template<GetStrategy_, T, optional_get_variant_type, Properties>  //
                          and Strategable_template<GetStrategy_, const T, optional_get_variant_const_type, Properties>;

template <>
struct GetStrategy_<Default> {
    template <Properties P>
    constexpr auto operator()(Gettingable auto& obj) const;  // for const and non-const calls
};
