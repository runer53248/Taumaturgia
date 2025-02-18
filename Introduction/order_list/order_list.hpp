#pragma once

#include "Taumaturgia/Properties/UserProperty.hpp"

using i_p1 = AdvanceUserProperty<int, struct first_int>;
using i_p2 = AdvanceUserProperty<int, struct second_int, struct int_tag>;
using i_p3 = AdvanceUserProperty<int, struct third_int>;
using f_p = UserPropertyAdapter<float>;

using s_p1 = AdvanceUserProperty<std::string, struct first_string>;
using s_p2 = AdvanceUserProperty<std::string, struct second_string>;

template <typename T>
using i_p1_t = i_p1::template type<T>;
template <typename T>
using i_p2_t = i_p2::template type<T>;
template <typename T>
using i_p3_t = i_p3::template type<T>;
template <typename T>
using f_p_t = f_p::template type<T>;

using order_list = taged_list<
    i_p1::order,
    i_p2::order,
    i_p3::order,
    f_p_t,
    s_p1::order,
    s_p2::order>;
