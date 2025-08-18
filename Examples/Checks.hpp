#pragma once
#include <iostream>

template<bool B>
inline void check_aP() {
#ifdef WITH_ADD_PROPERTIES
    if constexpr (B) {
        std::cout << "\n!!! aP ok !!!\n";
    } else {
        std::cout << "\n!!! aP version can be removed !!!\n";
    }
#endif
}
