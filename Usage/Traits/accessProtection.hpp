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

struct accessProtection : public accessType<Protection> {  // inheritance
    template <typename T>
    static const bool is_accessable = helpers::accessable<T, accessProtection, Protection>;

    template <helpers::ProtectionAccessable T>
        requires(not accessType<Protection>::is_accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.protection);
    }

    template <helpers::GetProtectionAccessable T>
        requires(not accessType<Protection>::is_accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getProtection();
    }

    using accessType<Protection>::get;
};

}  // namespace traits

template <>
struct trait_<Protection> {
    using type = traits::accessProtection;
};
