#pragma once
#include <utility>  // for as_const
#include "Helpers/same_as_ref.hpp"
#include "Helpers/trait_accessable.hpp"
#include "Helpers/traits_helper.hpp"

namespace traits {

template <typename T, typename TYPE>
concept GetTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE>() } -> same_as_ref<TYPE>;
    { std::as_const(x).template getType<TYPE>() } -> same_as_ref<const TYPE>;
};

template <typename TYPE, typename T>
struct CustomAccessType;

template <typename T, typename TYPE>
concept CustomTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(x) } -> same_as_ref<TYPE>;
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(std::as_const(x)) } -> same_as_ref<const TYPE>;
};

template <typename TYPE>
struct accessType {
    template <GetTypeAccessable<TYPE> T>
        requires(not CustomTypeAccessable<T, TYPE>)  // prefer custom access getters
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<TYPE>();
    }

    template <CustomTypeAccessable<TYPE> T>
        requires(not GetTypeAccessable<TYPE, T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }
};

}  // namespace traits

template <typename T, typename RESULT_TYPE>
concept accessType_trait_able = trait_accessable<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_template_able = traits::GetTypeAccessable<T, RESULT_TYPE>;
