#pragma once
#include "Taumaturgia/Properties/access_features.hpp"

class Protection;

namespace traits::helpers {

template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getProtection() } -> std::same_as<Protection&>;
    { std::as_const(x).getProtection() } -> std::same_as<const Protection&>;
};

}  // namespace traits::helpers

namespace traits {

struct accessProtection {
    using general_access_type = accessType<Protection>;  //[x]:  composition accessType<Protection>

    template <typename T>
    static const bool general_accessable = general_access_type::is_accessable<T>;

    template <typename T>
    static const bool is_accessable = helpers::accessable<T, accessProtection, Protection> or general_accessable<T>;

    template <helpers::ProtectionAccessable T>
        requires(not(helpers::GetProtectionAccessable<T> or CustomAccessType_able<T, Protection>))  // prefer getProtection() when both protection and getProtection() are visible
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.protection);
    }

    template <helpers::GetProtectionAccessable T>
        requires(not CustomAccessType_able<T, Protection>)  // prefer custom access more
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getProtection();
    }

    template <typename T>
        requires((not(helpers::ProtectionAccessable<T> or helpers::GetProtectionAccessable<T>) and general_accessable<T>) or CustomAccessType_able<T, Protection>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return general_access_type::get(el);
    }
};

}  // namespace traits

template <>
struct trait_<Protection> {
    using type = traits::accessProtection;
};
