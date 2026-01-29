#pragma once

#include "Taumaturgia/Properties/UserProperty.hpp"

using double_first = UserPropertyAdapter<double, Tags<struct first_double>>;
using double_second = UserPropertyAdapter<double, Tags<struct second_double>>;

using int_first = UserPropertyAdapter<int, Tags<struct first_int>>;
using int_second_tag = UserPropertyAdapter<int, Tags<struct second_int, struct int_tag>>;
using int_third = UserPropertyAdapter<int, Tags<struct third_int>>;

using just_float = UserPropertyAdapter<float>;

using just_int = UserPropertyAdapter<int>;

using string_first = UserPropertyAdapter<std::string, Tags<struct first_string>>;
using string_second = UserPropertyAdapter<std::string, Tags<struct second_string>>;

using order_list = taged_list<
    double_first::once,
    double_second::once,
    int_first::once,
    int_second_tag::once,
    int_third::once,
    just_float::once,
    string_first::once,
    string_second::once>;
