#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Usage/Properties.hpp"

#include <functional>

struct Empty {};

struct Name_health {
    Name name;
    Health hp;
};

using Type_naming = add_properties_ordered<
    Empty,
    Naming>;

using Type_living_naming = add_properties_ordered<
    Type_naming,
    Living>;

using Type2_living_naming = add_properties_ordered<
    Empty,
    Naming,
    Living>;
using Type3_living_naming = add_properties_ordered<
    Empty,
    Living,
    Naming>;

static_assert(sizeof(Name_health) == sizeof(Type_living_naming));
static_assert(sizeof(Name_health) == sizeof(Type2_living_naming));
static_assert(sizeof(Name_health) == sizeof(Type3_living_naming));
static_assert(std::is_same_v<Type2_living_naming, Type3_living_naming>);

struct Type_all {
    Name name;
    Health hp;
    WearContainer armorWear;
    Damage dmg;
    Protection protection;
    CureHealth cureHealth;
    EffectTypeContainer restoreEffects;
};
static_assert(Namingable<Type_all>);
static_assert(Livingable<Type_all>);
static_assert(Protectingable<Type_all>);
static_assert(Damagingable<Type_all>);
static_assert(Wearingable<Type_all>);
static_assert(Healingable<Type_all>);
static_assert(Restoringable<Type_all>);

int main() {
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
