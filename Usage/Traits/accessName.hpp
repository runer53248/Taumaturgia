#pragma once
#include <string>
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class Name;

namespace traits {
namespace helpers {

template <typename T>
concept NameAccessable = requires(T x) {
    x.name;
    requires std::is_convertible_v<decltype(T::name), std::string>;
};

template <typename T>
concept GetNameAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getName() } -> std::convertible_to<std::string>;
    { std::as_const(x).getName() } -> std::convertible_to<const std::string>;
};

}  // namespace helpers

struct accessName : public impl::accessType<Name, std::string> {
    template <typename T>
    static const bool accessable = helpers::trait_access_convertable<T, accessName, std::string>;

    template <helpers::NameAccessable T>
        requires(not accessType<Name, std::string>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.name);
    }

    template <helpers::GetNameAccessable T>
        requires(not accessType<Name, std::string>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    using accessType<Name, std::string>::get;
};

}  // namespace traits

template <>
struct trait_<Name> {
    using type = traits::accessName;
};
