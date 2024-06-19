#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Types/VariantType.hpp"
#include "Usage/Traits.hpp"

enum class Properties;

template <typename T>
struct GetStrategy_ {};

template <typename T>
concept Gettingable = Damagingable<T> or Healingable<T> or Livingable<T> or Protectingable<T> or Restoringable<T> or Wearingable<T>;

template <typename T>
concept is_custom_get_strategy = Strategable_template<GetStrategy_, T, optional_get_variant_type, Properties>  //
                          and Strategable_template<GetStrategy_, const T, optional_get_variant_const_type, Properties>;

template <typename T>
using GetStrategy = std::conditional_t<
    Gettingable<T>,
    std::conditional_t<
        is_custom_get_strategy<T>,
        GetStrategy_<T>,
        GetStrategy_<Default>>,
    GetStrategy_<T>>;
