#pragma once

enum class DurationType : size_t {
    Instant = 0,
    Action = 1,
    Round = 2,
    Minute = 20,
    Hour = 1200,
    Day = 28'800
};
