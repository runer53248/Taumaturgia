#pragma once
#include <string>
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

struct accessName /*: public accessType<Name, std::string>*/ {
    using general_access_type = accessType<Name, std::string>;
    template <typename T>
    static const bool general_accessable = general_access_type::accessable<T>;

    template <typename T>
    static const bool accessable = helpers::trait_access_convertable<T, accessName, std::string> or general_accessable<T>;

    template <helpers::NameAccessable T>
    // requires(not general_accessable<T>)
        requires(not(helpers::GetNameAccessable<T> or helpers::CustomTypeAccessable<T, Name, std::string>))  // prefer getName() when both name and getName() are visible
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.name);
    }

    template <helpers::GetNameAccessable T>
    // requires(not general_accessable<T>)
        requires(not helpers::CustomTypeAccessable<T, Name, std::string>)  // prefer custom access more
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    // using accessType<Name, std::string>::get;

    template <typename T>
        requires((not(helpers::NameAccessable<T> or helpers::GetNameAccessable<T>) and general_accessable<T>) or helpers::CustomTypeAccessable<T, Name, std::string>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return general_access_type::get(el);
    }
};

}  // namespace traits

template <>
struct trait_<Name> {
    using type = traits::accessName;
};
