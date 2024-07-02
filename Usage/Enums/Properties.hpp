#pragma once

enum class Properties {
    Health,
    CureHealth,
    Damage,
    Protection,
    Restore,
    Wear,
    Name,
    Get
};

template <Properties P>
struct sProperties {};
