#pragma once
#include <boost/mp11.hpp>

#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        constexpr bool have_all_types_from_args = (trait_accessable<ClassName, std::remove_cvref_t<Args>> and ...);           \
        if constexpr (have_all_types_from_args) {                                                                             \
            ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                 \
        } else {                                                                                                              \
            static_assert(have_all_types_from_args, "Unordered c-tor arguments contains type not accessable by traits.");     \
        }                                                                                                                     \
    }
