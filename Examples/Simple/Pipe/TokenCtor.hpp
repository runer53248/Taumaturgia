#pragma once
#include <boost/mp11.hpp>

#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                     \
    }
