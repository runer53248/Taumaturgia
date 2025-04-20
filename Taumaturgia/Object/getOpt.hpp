#pragma once
#include <concepts>
#include "Usage/Enums/Properties.hpp"

template <Properties param, typename T>
    requires requires(T t) {
        t.template getOpt<param>();
    }
decltype(auto) getOpt(T& object) {
    return object.template getOpt<param>();
}
