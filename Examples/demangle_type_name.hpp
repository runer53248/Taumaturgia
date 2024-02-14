#pragma once
#include <boost/core/demangle.hpp>

template <class T>
std::string name() {
    return boost::core::demangle(typeid(T).name());
}
