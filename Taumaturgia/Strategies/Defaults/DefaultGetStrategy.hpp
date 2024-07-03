#pragma once
#include "default_get_behavior.hpp"

template <>
struct GetStrategy_<Default> {
    template <Properties PROPERTY, Gettingable GET_TYPE>
    constexpr auto operator()(GET_TYPE& obj) const -> get_result_type<PROPERTY, std::is_const_v<GET_TYPE>> {
        return default_get_behavior<PROPERTY>(obj);
    }
};
