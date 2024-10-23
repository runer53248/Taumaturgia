#pragma once
#include "default_get_behavior.hpp"

template <>
struct GetterStrategy_<Default> {
    template <Properties PROPERTY, Gettingable GET_TYPE>
    static constexpr auto operator()(GET_TYPE& obj) -> get_result_type<PROPERTY, std::is_const_v<GET_TYPE>> {
        return default_get_behavior<PROPERTY>(obj);
    }
};
