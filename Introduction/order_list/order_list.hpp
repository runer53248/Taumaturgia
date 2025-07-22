#pragma once

#include "Taumaturgia/Properties/UserProperty.hpp"

using double_first = UserPropertyAdapter<double, struct first_double>;
using double_second = UserPropertyAdapter<double, struct second_double>;

using int_first = UserPropertyAdapter<int, struct first_int>;
using int_second_tag = UserPropertyAdapter<int, struct second_int, struct int_tag>;
using int_third = UserPropertyAdapter<int, struct third_int>;

using just_float = UserPropertyAdapter<float>;

using just_int = UserPropertyAdapter<int>;

using string_first = UserPropertyAdapter<std::string, struct first_string>;
using string_second = UserPropertyAdapter<std::string, struct second_string>;

using order_list = taged_list<
    double_first::once,
    double_second::once,
    int_first::once,
    int_second_tag::once,
    int_third::once,
    just_float::once,
    string_first::once,
    string_second::once>;
