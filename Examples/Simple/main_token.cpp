// #define IGNORE_ORDER_LIST

#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Properties.hpp"

#include "Examples/demangle_type_name.hpp"

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                         \
    template <typename... Args>                                      \
    ClassName(const Token&, Args&&... args) noexcept {               \
        ((trait<Args>::get(*this) = std::forward<Args>(args)), ...); \
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
    // Name name;
    Damage dmg;
    Health hp;
    // Protection protection;
    double type{};

private:
    int type1{};
    float type2{};
};

int main() {
    std::cout << '\n';

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
        using type_1 = add_properties<
            Base,
            Living,
            Damaging,
            Protecting,
            Naming>;

        auto t1 = type_1{
            unordered,  // ignore order of arguments
            Damage{5, DamageType::Divine},
            Name{"Test"},
            float{3.14f},   // type<float>
            int{100},       // type<int>
            double{20.20},  // type<double>
            Health{100, 100},
            Protection{10, BodyLocation::Head},
        };

        print(t1);
    }

    {
        // create a properties_list
        using p_list = properties_list<
            Living,
            Damaging,
            Protecting,
            Naming>;

        // create a type
        using type_1 = p_list::apply_properties<Base>;

        auto t1 = type_1{
            unordered,      // ignore order of arguments
            float{3.14f},   // type<float>
            int{100},       // type<int>
            double{20.20},  // type<double>
            Protection{10, BodyLocation::Head},
            Damage{5, DamageType::Magical},
            Name{"Test"},
            Health{100, 100},
        };

        print(t1);
    }
}
