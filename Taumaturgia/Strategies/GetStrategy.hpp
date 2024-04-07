#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Gettingable.hpp"
#include "Taumaturgia/Types/VariantType.hpp"

enum class Parameter;

struct Default;
class Object;

template <typename T>
struct GetStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept GetStrategable = requires(Strategy<UserType> strategy, UserType& type, const UserType& ctype, Parameter param) {
    { strategy.template operator()<Parameter{}>(type) } -> std::same_as<get_optional_variant_type>;
    { strategy.template operator()<Parameter{}>(ctype) } -> std::same_as<get_optional_variant_const_type>;
};

template <typename T>
using GetStrategy = std::conditional_t<
    Gettingable<T>,
    std::conditional_t<
        GetStrategable<GetStrategy_, T>,
        GetStrategy_<T>,
        GetStrategy_<Default>>,
    GetStrategy_<T>>;

template <typename T>
concept is_get_strategy = GetStrategable<GetStrategy, T>;

template <>
struct GetStrategy_<Default> {
    template <Parameter P>
    auto operator()(Gettingable auto& obj) const;  // for const and non-const calls
};
