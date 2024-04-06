#pragma once
#include <stdexcept>

class Object;

inline Object* Whom(Object* const owner, Object* const target) {
    if (not owner and not target) {
        throw std::logic_error("Whom function get nullptr as both object owner and target.");
    }

    if ((owner == target) or not target) {
        return owner;
    }
    return target;
}
