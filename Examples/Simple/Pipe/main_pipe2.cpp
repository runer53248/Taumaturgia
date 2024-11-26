#include "Base.hpp"
#include "With.hpp"
#include "default_values.hpp"

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

int main() {
    std::cout << '\n';

    // MARK: print lambda

    auto print = [](auto type) {
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "x      = " << type.x << '\n';
        std::cout << "y      = " << type.y << '\n';
        std::cout << "int    = " << trait<int>::get(type) << '\n';
        std::cout << "float  = " << trait<float>::get(type) << '\n';
        std::cout << "double = " << trait<double>::get(type) << '\n';
        std::cout << '\n';
    };

    {
        auto create_type =
            From::base<Base>              //
            | With::Name                  //
            | With::Health                //
            | With::Damage                //
            | With::Protection            //
            | With::property<Protecting>  //
            ;

        auto type1 = create_type(
            unordered,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            float{3.14f},
            Protection{10, BodyLocation::Head},
            default_int,
            double{20.20},
            Name{"Test"});

        auto type2 = create_type(
            unordered,  // ignore order of arguments
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name);

        print(type1);
        print(type2);
    }
    {
        auto create_type =
            From::base<Base>              //
            | WithUnordered::Name                  //
            | WithUnordered::Health                //
            | WithUnordered::Damage                //
            | WithUnordered::Protection            //
            | WithUnordered::property<Protecting>  //
            ;

        auto type1 = create_type(
            unordered,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            float{3.14f},
            Protection{10, BodyLocation::Head},
            default_int,
            double{20.20},
            Name{"Test"});

        auto type2 = create_type(
            unordered,  // ignore order of arguments
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name);

        print(type1);
        print(type2);
    }
}
