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
struct Deduced {};

namespace DeduceProperties {
using ::Deduced;
using ::Properties;

constexpr static Deduced<Properties::Health> Health{};
constexpr static Deduced<Properties::CureHealth> CureHealth{};
constexpr static Deduced<Properties::Damage> Damage{};
constexpr static Deduced<Properties::Protection> Protection{};
constexpr static Deduced<Properties::Restore> Restore{};
constexpr static Deduced<Properties::Wear> Wear{};
constexpr static Deduced<Properties::Name> Name{};
constexpr static Deduced<Properties::Get> Get{};
}  // namespace DeduceProperties
