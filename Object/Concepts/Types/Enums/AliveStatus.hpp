#pragma once

enum class AliveStatus : signed char {
    // Unknown = -127,
    // Undeath = -3,
    // Destroyed = -2,
    Death = -1,
    Dying = 0,
    // Critical_Wounded = 20,
    // Serious_Wounded = 40,
    // Moderate_Wounded = 60,
    // Light_Wounded = 80,
    Healthy = 100,
    Living = 100
    // Overflow_Healthy = 110,
    // Immortal = 128
};
