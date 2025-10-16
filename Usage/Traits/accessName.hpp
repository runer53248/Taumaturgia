#pragma once
#include <string>
#include "Taumaturgia/Properties/access_features.hpp"

class Name;

namespace traits::helpers {

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

}  // namespace traits::helpers

namespace traits {

struct accessName /*: public accessType<Name, std::string>*/ {
    using general_access_type = accessType<Name, std::string>;  // composition
    template <typename T>
    static const bool general_accessable = general_access_type::is_accessable<T>;

    template <typename T>
    static const bool is_accessable = helpers::accessable<T, accessName, Name, std::string> or general_accessable<T>;

    template <helpers::NameAccessable T>
        requires(not(helpers::GetNameAccessable<T> or CustomAccessType_able<T, Name, std::string>))  // prefer getName() when both name and getName() are visible
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.name);
    }

    template <helpers::GetNameAccessable T>
        requires(not CustomAccessType_able<T, Name, std::string>)  // prefer custom access more
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    // using accessType<Name, std::string>::get;

    template <typename T>
        requires((not(helpers::NameAccessable<T> or helpers::GetNameAccessable<T>) and general_accessable<T>) or CustomAccessType_able<T, Name, std::string>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return general_access_type::get(el);
    }
};

}  // namespace traits

template <>
struct trait_<Name> {
    using type = traits::accessName;
};
