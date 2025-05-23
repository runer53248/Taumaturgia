#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/Properties.hpp"

constexpr bool with_ignore_order_list = true;

template <typename T, template <typename...> typename... properties>
using add_properties_type = std::conditional_t<
    with_ignore_order_list,
    add_properties_unordered<T, properties...>,
    add_properties_ordered<T, properties...>>;

#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        constexpr bool have_all_types_from_args = (trait_accessable<ClassName, std::remove_cvref_t<Args>> and ...);           \
        if constexpr (have_all_types_from_args) {                                                                             \
            ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                 \
        } else {                                                                                                              \
            static_assert(have_all_types_from_args, "Unordered c-tor arguments contains type not accessable by traits.");     \
        }                                                                                                                     \
    }

struct Base {
    Base() noexcept = default;
    TokenCtor(Base);

    template <typename T, size_t = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (std::same_as<T, int>) {
            return (self.type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (self.type2);
        }
        // if constexpr (std::same_as<T, double>) {
        //     return (self.type);
        // }
    }

    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};

private:
    // double type{};
    int type1{};
    float type2{};
};

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
        // create a type
        using Type_0_5 = add_properties_type<
            Base,
            Damaging,
            Living>;
        using Type_1 = add_properties_type<
            Type_0_5,
            Protecting,
            Naming>;

        // create a properties_list
        using p_list = properties_list<
            Damaging,
            Living>;
        using p_list_2 = properties_list<
            Protecting,
            Naming>;

        // create a type
        using Type_1_5 = p_list::apply_properties_to<Base, not with_ignore_order_list>;
        using Type_2 = p_list_2::apply_properties_to<Type_1_5, not with_ignore_order_list>;

        static_assert(std::same_as<Type_1, Type_2>);

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

        auto type2 = Type_1{
            unordered,  // ignore order of arguments
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name};

        print(type1);
        print(type2);
    }
}
