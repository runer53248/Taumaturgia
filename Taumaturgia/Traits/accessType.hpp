#pragma once
#include "TypeConcepts.hpp"

// TODO: make accessType::get for tagged access

namespace traits::impl {

template <typename TYPE, typename CONVERT_TYPE = void>
struct accessType {
    template <typename T>
    static constexpr bool accessable = (std::is_same_v<CONVERT_TYPE, void>)
                                           ? helpers::trait_accessable<T, accessType<TYPE>, TYPE>
                                           : helpers::trait_access_convertable<T, accessType<TYPE, CONVERT_TYPE>, CONVERT_TYPE>;

    template <helpers::TypeAccessable<TYPE> T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.type);
    }

    template <helpers::GetTypeAccessable<TYPE> T>
        requires(not(helpers::CustomTypeAccessable<T, TYPE, CONVERT_TYPE> or helpers::GetTypeTemplateAccessable<T, TYPE>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getType();
    }

    template <helpers::GetTypeTemplateAccessable<TYPE> T>
        requires(not helpers::CustomTypeAccessable<T, TYPE, CONVERT_TYPE>)  // prefer custom access getters
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<TYPE>();
    }

    template <helpers::CustomTypeAccessable<TYPE, CONVERT_TYPE> T>
        requires(not helpers::GetTypeTemplateAccessable<TYPE, T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }
};

}  // namespace traits::impl

template <typename T, typename RESULT_TYPE>
concept accessType_trait_able = traits::helpers::trait_accessable<T, traits::impl::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_template_able = traits::helpers::GetTypeTemplateAccessable<T, RESULT_TYPE>;
