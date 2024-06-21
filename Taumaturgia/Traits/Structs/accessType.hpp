#pragma once
#include "Concepts/TypeConcepts.hpp"

namespace traits {

template <typename TYPE>
struct accessType {
    static auto& get(TypeAccessable<TYPE> auto& el) noexcept {
        return el.type;
    }

    template <GetTypeAccessable<TYPE> T>
        requires(not(CustomTypeAccessable<T, TYPE> or GetTypeTemplateAccessable<T, TYPE>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getType();
    }

    template <GetTypeTemplateAccessable<TYPE> T>
        requires(not CustomTypeAccessable<T, TYPE>)  // prefer custom access getters
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<TYPE>();
    }

    template <CustomTypeAccessable<TYPE> T>
        requires(not GetTypeTemplateAccessable<TYPE, T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }
};

}  // namespace traits
