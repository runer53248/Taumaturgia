#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/Properties.hpp"

#include "Base.hpp"

enum class As { given,
                order_list };

constexpr auto with_ignore_order_list = As::given;

template <As order_type, typename T, template <typename...> typename... properties>
using add_properties_type = std::conditional_t<
    order_type == As::given,
    add_properties_unordered<T, properties...>,
    add_properties_ordered<T, properties...>>;

int main() {
    std::cout << '\n';

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
        using Type_1 = p_list::apply_properties_to<Base, with_ignore_order_list == As::order_list>;
        using Type_2 = p_list_2::apply_properties_to<Type_1, with_ignore_order_list == As::order_list>;

        static_assert(std::same_as<Type_1, Type_2>);
    }

    {
        using Type_A = add_properties_type<
            As::given,
            Base,
            Damaging,
            Living>;

        using Type_1 = add_properties_type<
            As::given,
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

        std::cout << parse_type_name<Type_1>() << '\n';
        print(type1);
    }

    {
        using Type_A = add_properties_type<
            As::order_list,
            Base,
            Damaging,
            Living>;

        using Type_1 = add_properties_type<
            As::order_list,
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

        std::cout << parse_type_name<Type_1>() << '\n';
        print(type1);
    }
}
