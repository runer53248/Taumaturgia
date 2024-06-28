#pragma once

enum class Properties {
    Health,
    CureHealth,
    Damage,
    Protection,
    Restore,
    Wear,
    Get
};

template <Properties P>
struct sProperties {};
