#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Usage/Properties.hpp"

struct EmptyType {};

using Type_named = Naming<EmptyType>;

using Type_5 = add_properties_ordered<
    Type_named,
    Healing,
    Protecting,
    Restoring,
    Living,
    Wearing,
    Damaging>;

int main() {
    {
        Type_5 type1{};  // all properties defaulted
        Type_5 type2{Name{"Valid"},
                     Health{50}};  // rest of properties defaulted
        Type_5 type3{Name{"Valid"},
                     std::ignore,
                     std::ignore,
                     std::ignore,
                     std::ignore,
                     CureHealth{25},
                     std::ignore};  // ignore some of properties
        Type_5 type4{Name{"Valid"},
                     Health{25},
                     WearContainer{},
                     Damage{},
                     Protection{},
                     CureHealth{},
                     EffectTypeContainer{}};  // set all properties

        int index = 1;
        for (auto& type : {type1, type2, type3, type4}) {
            std::cout << "type" << index++ << " Name:         " << trait<Name>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type1, type2, type3, type4}) {
            std::cout << "type" << index++ << " Hp:           " << trait<Health>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type1, type2, type3, type4}) {
            std::cout << "type" << index++ << " CureHealth:   " << trait<CureHealth>::get(type) << '\n';
        }
        std::cout << '\n';
    }

    {  // types used in CureHealth C-tor

        using health_tuple = std::tuple<int, EffectContainer>;    // types used in Health C-tor
        using wear_tuple = std::tuple<int>;                       // types used in WearContainer C-tor
        using cureHealth_tuple = std::tuple<int, CureValueType>;  // types used in CureHealth C-tor

        using variant_type_2 = std::variant<
            Damage>;

        using variant_type_1 = std::variant<
            Health,
            WearContainer,
            Damage,
            Protection,
            CureHealth,
            EffectTypeContainer>;

        auto vec = std::vector<variant_type_1>{
            Health{125},
            WearContainer{},
            Damage{20, DamageType::Magical},
            Protection{3},
            CureHealth{1},
            EffectTypeContainer{}};

        auto varDmg = variant_type_2{Damage{120, DamageType::Divine}};

        Type_5 type5_1{Name{"Valid"},
                       health_tuple{25, {Effect{EffectType::Burn}, Effect{EffectType::Freeze}}},  // tuple
                       wear_tuple{10},                                                            // tuple
                       Damage{},
                       std::ignore,
                       cureHealth_tuple{10, CureValueType::MAX_PERCENT},  // tuple
                       EffectTypeContainer{}};                            // create properties from tuples
        Type_5 type5_2{Name{"Valid"},
                       vec[0],
                       vec[1],
                       vec[2],
                       vec[3],
                       vec[4],
                       vec[5]};  // create properties from variants
        Type_5 type5_3{Name{"Valid"},
                       varDmg,
                       varDmg,
                       varDmg};  // create properties from wrong variants

        int index = 1;
        for (auto& type : {type5_1, type5_2, type5_3}) {
            std::cout << "type5_" << index++ << " HP:       " << trait<Health>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type5_1, type5_2, type5_3}) {
            std::cout << "type5_" << index++ << " Armor:    " << trait<WearContainer>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type5_1, type5_2, type5_3}) {
            std::cout << "type5_" << index++ << " Protection:    " << trait<Protection>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type5_1, type5_2, type5_3}) {
            std::cout << "type5_" << index++ << " CureHp:   " << trait<CureHealth>::get(type) << '\n';
        }
        index = 1;
        for (auto& type : {type5_1, type5_2, type5_3}) {
            std::cout << "type5_" << index++ << " Damage:   " << trait<Damage>::get(type) << '\n';
        }
        std::cout << '\n';
    }
    {
#ifdef USES_ADD_PROPERTIES
        check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
