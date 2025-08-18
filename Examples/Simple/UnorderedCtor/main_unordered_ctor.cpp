#include "../Base.hpp"
#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/Properties.hpp"

int main() {
    [[maybe_unused]] int default_int{100};
    [[maybe_unused]] float default_float{3.14f};
    [[maybe_unused]] double default_double{20.20};
    [[maybe_unused]] Health default_health{100, 100};
    [[maybe_unused]] Damage default_damage{5, DamageType::Divine};
    [[maybe_unused]] Protection default_protection{10, BodyLocation::Head};
    [[maybe_unused]] Name default_name{"Test"};

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
        // create a properties_list
        using p_list = properties_list<
            Damaging,
            Living>;
        using p_list_2 = properties_list<
            Protecting,
            Naming>;

        // create a type
        using Type_1a = p_list::apply_properties_to<Base, false>;
        using Type_2a = p_list_2::apply_properties_to<Type_1a, false>;
        static_assert(std::same_as<Type_1a, Type_2a>);

        using Type_1b = p_list::apply_properties_to<Base, true>;
        using Type_2b = p_list_2::apply_properties_to<Type_1b, true>;
        static_assert(std::same_as<Type_1b, Type_2b>);
    }

    {
        using Type_A = add_properties_unordered<
            Base,
            Damaging,
            Living>;

        using Type_1 = add_properties_unordered<
            Type_A,
            Protecting,
            Naming>;

        auto type1 = Type_1{
            unordered,      // ignore order of arguments
            float{3.14f},   // type<float>
            default_int,    // type<int>
            double{20.20},  // type<double>
            Protection{10, BodyLocation::Head},
            Damage{5, DamageType::Magical},
            Name{"Test"},
            Health{100, 100},
        };

        std::cout << parse_type_name<Type_1, float, double>() << '\n';
        print(type1);
    }

    {
        using Type_A = add_properties_ordered<
            Base,
            Damaging,
            Living>;

        using Type_1 = add_properties_ordered<
            Type_A,
            Protecting,
            Naming>;

        auto type1 = Type_1{
            unordered,  // ignore order of arguments
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name};

        std::cout << parse_type_name<Type_1, float, double>() << '\n';
        print(type1);
    }

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
