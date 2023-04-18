#pragma once

enum class BodyLocation : size_t {
    NONE,
    Head,
    Body,
    Arms,
    Legs,
    Internal,
    ALL  // used as number of elements for array and as special value to accumulate values from it
};
