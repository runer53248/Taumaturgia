// #define IGNORE_ORDER_LIST

#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/Properties.hpp"

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                     \
    }

struct Base {
    Base() noexcept = default;
    TokenCtor(Base);

    template <typename T, size_t = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (std::same_as<T, int>) {
            return (type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (type2);
        }
    }
    template <typename T, size_t = 0>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (std::same_as<T, int>) {
            return (type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (type2);
        }
    }

    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};

private:
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
        using Type_0_5 = add_properties<
            Base,
            Damaging,
            Living>;
        using Type_1 = add_properties<
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
        using Type_1_5 = p_list::apply_properties<Base>;
        using Type_2 = p_list_2::apply_properties<Type_1_5>;

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
