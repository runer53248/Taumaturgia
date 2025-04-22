#pragma once
#include "Helpers/traits_helper.hpp"

// TODO: make accessType::get for tagged access

namespace traits {

template <typename TYPE, typename CONVERT_TYPE = void>
struct accessType {
    template <typename T>
    static constexpr bool is_accessable = helpers::accessable<T, accessType<TYPE, CONVERT_TYPE>, TYPE, CONVERT_TYPE>;

    template <type_able<TYPE> T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.type);
    }

    template <getType_able<TYPE> T>
        requires(not(CustomAccessType_able<T, TYPE, CONVERT_TYPE> or getType_template_able<T, TYPE>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getType();
    }

    template <getType_template_able<TYPE> T>
        requires(not CustomAccessType_able<T, TYPE, CONVERT_TYPE>)  // prefer custom access getters
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<TYPE>();
    }

    template <CustomAccessType_able<TYPE, CONVERT_TYPE> T>
        requires(not getType_template_able<TYPE, T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(el);
    }

    //

    // template <typename... TTags, typename T>
    //     requires requires {
    //         T::template getTypeTaged<TYPE, TTags...>();
    //     }
    // static constexpr decltype(auto) getTypeTaged(T& el) noexcept {
    //     return T::template getTypeTaged<TYPE, TTags...>();
    // }
};

}  // namespace traits
