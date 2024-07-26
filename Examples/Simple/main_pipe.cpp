// #define IGNORE_ORDER_LIST

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Strategies.hpp"

#include "Examples/demangle_type_name.hpp"

#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

namespace With {
[[maybe_unused]] constexpr Property<Naming> Name{};
[[maybe_unused]] constexpr Property<Damaging> Damage{};
[[maybe_unused]] constexpr Property<Healing> CureHealth{};
[[maybe_unused]] constexpr Property<Living> Health{};
[[maybe_unused]] constexpr Property<Protecting> Protection{};
[[maybe_unused]] constexpr Property<Restoring> EffectTypeContainer{};
[[maybe_unused]] constexpr Property<Wearing> WearContainer{};
};  // namespace With

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                         \
    template <type_of<Token> Arg, typename... Args>                  \
    ClassName(Arg&, Args&&... args) noexcept {                       \
        ((trait<Args>::get(*this) = std::forward<Args>(args)), ...); \
    }

struct Base {
    Base() noexcept = default;

    Base(int x, int y) noexcept
        : x{x}, y{y} {}

    TokenCtor(Base);

    template <typename T>
    constexpr decltype(auto) getType() noexcept {
        if constexpr (std::same_as<T, int>) {
            return (type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (type2);
        }
    }
    template <typename T>
    constexpr decltype(auto) getType() const noexcept {
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
    {
        // create a type
        using type_1 = add_properties<
            Base,
            Living,
            Damaging,
            Protecting,
            Naming>;

        auto t1 = type_1{
            token,  // ignore order of arguments
            Damage{5, DamageType::Divine},
            Health{100, 100},
            Protection{10, BodyLocation::Head},
            Name{"Test"},
        };

        std::cout << name<decltype(t1)>() << '\n';
        std::cout << trait<Name>::get(t1) << '\n';
        std::cout << trait<Damage>::get(t1) << '\n';
        std::cout << trait<Protection>::get(t1) << '\n';
        std::cout << trait<Health>::get(t1) << '\n';
        std::cout << t1.x << '\n';
        std::cout << t1.y << '\n';
        std::cout << '\n';
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
            token,  // ignore order of arguments
            Damage{5, DamageType::Divine},
            Health{100, 100},
            Protection{10, BodyLocation::Head},
            Name{"Test"},
        };

        std::cout << name<decltype(t1)>() << '\n';
        std::cout << trait<Name>::get(t1) << '\n';
        std::cout << trait<Damage>::get(t1) << '\n';
        std::cout << trait<Protection>::get(t1) << '\n';
        std::cout << trait<Health>::get(t1) << '\n';
        std::cout << t1.x << '\n';
        std::cout << t1.y << '\n';
        std::cout << '\n';
    }

    constexpr auto default_x = 12;
    constexpr auto default_y = 5;

    {
        // create a lambda factory
        auto create_type_2 =
            Base{default_x, default_y}  // ! ignore prototype and use default c-tor
            | With::Name                //
            | With::Health              //
            | With::Damage              //
            | With::Protection          //
            ;

        auto t2 = create_type_2(
            token,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        std::cout << "x = " << default_x << " | " << t2.x << '\n';  // ! should remember x value
        std::cout << "y = " << default_y << " | " << t2.y << '\n';  // ! should remember x value

        std::cout << name<decltype(t2)>() << '\n';
        std::cout << trait<Name>::get(t2) << '\n';
        std::cout << trait<Damage>::get(t2) << '\n';
        std::cout << trait<Protection>::get(t2) << '\n';
        std::cout << trait<Health>::get(t2) << '\n';
        std::cout << t2.x << '\n';
        std::cout << t2.y << '\n';

        std::cout << '\n';
    }

    {
        auto tlist = With::Name | With::Health | With::Protection | With::Damage;

        // Base base{default_x, default_y};  // target
        // auto tp = base | tlist;           // modify existing target type
        auto tp = Base{default_x, default_y} | tlist;

        std::cout << "x = " << default_x << " | " << tp.x << '\n';
        std::cout << "y = " << default_y << " | " << tp.y << '\n';
        std::cout << "tlist =  " << name<decltype(tlist)>() << '\n';
        std::cout << "tlist2 = " << name<decltype(tlist)>() << '\n';
        std::cout << "tp =     " << name<decltype(tp)>() << '\n';
        std::cout << '\n';

        {                              // extra example
            list tlist2 = With::Name;  // ? implicit conversion needed (don't use auto)
            auto tlist3 = With::Name;  // !

            auto tp2 = Base{default_x, default_y} | tlist2;
            auto tp3 = Base{default_x, default_y} | tlist3;  // ! creator

            std::cout << "tp2 =    " << name<decltype(tp2)>() << '\n';
            std::cout << "tp3 =    " << name<decltype(tp3)>() << '\n';  // ! creator
            std::cout << '\n';
        }

        // update rest of target parameters
        auto update = [](auto& target) {
            return [&target]<typename... Args>
                requires(trait<Args>::template accessable<std::remove_cvref_t<decltype(target)>> and ...)
            (Args&&... args) {
                ((trait<Args>::get(target) = std::forward<Args>(args)), ...);
            };
        };

        // static_assert(trait<float>::template accessable<decltype(tp)>);
        // static_assert(traits::TypeAccessable<decltype(tp), float>);

        static_assert(trait<double>::template accessable<decltype(tp)>);
        static_assert(traits::TypeAccessable<decltype(tp), double>);

        update(tp)(
            Health{100, 100},
            int{100},      // type<int>
            float{3.14f},  // type<float>
            double{20.20},  // type<double>
            Damage{5},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        std::cout << name<decltype(tp)>() << '\n';
        std::cout << trait<Name>::get(tp) << '\n';
        std::cout << trait<Damage>::get(tp) << '\n';
        std::cout << trait<Protection>::get(tp) << '\n';
        std::cout << trait<Health>::get(tp) << '\n';
        std::cout << tp.x << '\n';
        std::cout << tp.y << '\n';
        std::cout << trait<int>::get(tp) << '\n';
        std::cout << trait<float>::get(tp) << '\n';
        std::cout << trait<double>::get(tp) << '\n';
    }
}
