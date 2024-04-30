#pragma once
#include <boost/core/demangle.hpp>
#include <typeinfo>

template <typename T>
inline std::string name() {
    using TR = std::remove_reference_t<T>;
    std::string r = boost::core::demangle(typeid(T).name());
    if (std::is_const<TR>::value) {
        r = "const " + r;
    }
    if (std::is_volatile<TR>::value) {
        r = "volatile " + r;
    }
    if (std::is_lvalue_reference<T>::value) {
        r += "&";
    } else if (std::is_rvalue_reference<T>::value) {
        r += "&&";
    }
    return r;
}
