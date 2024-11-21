#pragma once
#include "Usage/Properties.hpp"

[[maybe_unused]] constexpr auto default_x = 12;
[[maybe_unused]] constexpr auto default_y = 5;

[[maybe_unused]] int default_int{100};
[[maybe_unused]] float default_float{3.14f};
[[maybe_unused]] double default_double{20.20};
[[maybe_unused]] Health default_health{100, 100};
[[maybe_unused]] Damage default_damage{5, DamageType::Divine};
[[maybe_unused]] Protection default_protection{10, BodyLocation::Head};
[[maybe_unused]] Name default_name{"Test"};
