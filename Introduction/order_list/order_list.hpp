#pragma once

#include "Taumaturgia/Properties/UserProperty.hpp"

using double_first = AdvanceUserProperty<double, struct first_double>;
using double_second = AdvanceUserProperty<double, struct second_double>;

using int_first = AdvanceUserProperty<int, struct first_int>;
using int_second_tag = AdvanceUserProperty<int, struct second_int, struct int_tag>;
using int_third = AdvanceUserProperty<int, struct third_int>;

using just_float = UserPropertyAdapter<float>;

using just_int = AdvanceUserProperty<int>;

using string_first = AdvanceUserProperty<std::string, struct first_string>;
using string_second = AdvanceUserProperty<std::string, struct second_string>;

using order_list = taged_list<
    double_first::order,
    double_second::order,
    int_first::order,
    int_second_tag::order,
    int_third::order,
    just_float::type,
    string_first::order,
    string_second::order>;
