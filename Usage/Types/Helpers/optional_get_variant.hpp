#pragma once
#include <boost/mp11.hpp>
#include <optional>
#include <variant>
#include "list_of_types.hpp"

using get_variant_type = boost::mp11::mp_append<
    std::variant<std::monostate>,
    boost::mp11::mp_transform<
        std::reference_wrapper,
        list_of_types>>;

using get_variant_const_type = boost::mp11::mp_append<
    std::variant<std::monostate>,
    boost::mp11::mp_transform<
        std::reference_wrapper,
        boost::mp11::mp_transform<
            std::add_const_t,
            list_of_types>>>;

using optional_get_variant_type = std::optional<get_variant_type>;
using optional_get_variant_const_type = std::optional<get_variant_const_type>;

template <typename T>
using to_optional_get_variant = std::conditional_t<
    std::is_const_v<std::remove_reference_t<T>>,
    optional_get_variant_const_type,
    optional_get_variant_type>;

template <typename T>
concept is_optional_get_variant =
    std::same_as<std::remove_cvref_t<T>, optional_get_variant_type> or
    std::same_as<std::remove_cvref_t<T>, optional_get_variant_const_type>;

template <typename T>
concept is_get_variant =
    std::same_as<std::remove_cvref_t<T>, get_variant_type> or
    std::same_as<std::remove_cvref_t<T>, get_variant_const_type>;

template <typename T, typename TYPE>
concept is_ref_of_type =
    std::same_as<std::remove_cvref_t<T>, std::reference_wrapper<TYPE>> or
    std::same_as<std::remove_cvref_t<T>, std::reference_wrapper<const TYPE>>;
