#pragma once
#include <type_traits>
#include "Traits/CureHealthTraits.hpp"
#include "Types/CureHealth.hpp"

template <typename T>
concept Healingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessCureHealth::get(x) } -> same_as_ref<CureHealth>;
    { traits::accessCureHealth::get(std::as_const(x)) } -> same_as_ref<const CureHealth>;
};
