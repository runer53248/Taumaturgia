#pragma once
#include "TypeConcepts.hpp"

namespace traits {

template <typename TYPE, typename CONVERT_TYPE = void>
struct accessType {
    template <typename T>
    static constexpr bool accessable = (std::is_same_v<CONVERT_TYPE, void>)
                                           ? helpers::trait_accessable<T, accessType<TYPE>, TYPE>
                                           : helpers::trait_access_convertable<T, accessType<TYPE, CONVERT_TYPE>, CONVERT_TYPE>;

    template <TypeAccessable<TYPE> T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.type);
    }

    template <GetTypeAccessable<TYPE> T>
        requires(not(CustomTypeAccessable<T, TYPE, CONVERT_TYPE> or GetTypeTemplateAccessable<T, TYPE>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getType();
    }

    template <GetTypeTemplateAccessable<TYPE> T>
        requires(not CustomTypeAccessable<T, TYPE, CONVERT_TYPE>)  // prefer custom access getters
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<TYPE>();
    }

    template <CustomTypeAccessable<TYPE, CONVERT_TYPE> T>
        requires(not GetTypeTemplateAccessable<TYPE, T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }
};

}  // namespace traits

template <typename T, typename RESULT_TYPE>
concept accessType_trait_able = traits::helpers::trait_accessable<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_template_able = traits::GetTypeTemplateAccessable<T, RESULT_TYPE>;
