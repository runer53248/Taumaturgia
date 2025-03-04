#pragma once
#include <type_traits>
#include <utility>  // for as_const
#include "Taumaturgia/Traits/trait.hpp"

class Protection;

namespace traits {
namespace helpers {

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

}  // namespace helpers

struct accessProtection : public impl::accessType<Protection> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessProtection, Protection>;

    template <helpers::ProtectionAccessable T>
        requires(not accessType<Protection>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.protection);
    }

    template <helpers::GetProtectionAccessable T>
        requires(not accessType<Protection>::accessable<T>)
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
