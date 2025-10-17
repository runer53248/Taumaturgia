#pragma once
#include "Adapter.hpp"
#include "EmptyType.hpp"
#include "Usage/Types/Health/Health.hpp"

using NpcBuild = add_properties_ordered<
    Type,
    Adapter<Living, struct Npc_tag>::type  // Living taged for custom default value
    >;

template <>
struct UserDefaultValue<property_t<Living>, struct Npc_tag> {
    static constexpr auto value = [] { return property_t<Living>{5}; };
};

struct NpcClass {
    property_t<Living> hp{5};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Npc = NpcBuild;
#else
using Npc = NpcClass;
#endif
