#pragma once
#include <boost/core/demangle.hpp>
#include <typeinfo>

template <typename T>
inline std::string name() {
    return boost::core::demangle(typeid(T).name());
}
