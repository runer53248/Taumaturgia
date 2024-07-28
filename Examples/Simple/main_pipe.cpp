// #define IGNORE_ORDER_LIST

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Properties.hpp"

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

template <template <typename> typename P>
[[maybe_unused]] constexpr Property<P> property{};
};  // namespace With

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                         \
    template <typename... Args>                                      \
    ClassName(const Token&, Args&&... args) noexcept {               \
        ((trait<Args>::get(*this) = std::forward<Args>(args)), ...); \
    }

struct Base {
    Base() noexcept = default;

    Base(int x, int y) noexcept
        : x{x}, y{y} {}

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
    // Health hp;
    Protection protection;
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

    constexpr auto default_x = 12;
    constexpr auto default_y = 5;

    {
        Base base{default_x, default_y};

        // create a lambda factory
        auto create_type_2 =
            base                // ! ignore prototype and use default c-tor
            | With::Name        //
            | With::Health      //
            | With::Damage      //
            | With::Protection  //
            | With::property<Protecting>;

        auto t2 = create_type_2(
            unordered,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            float{3.14f},  // type<float>
            Protection{10, BodyLocation::Head},
            int{100},       // type<int>
            double{20.20},  // type<double>
            Name{"Test"});

        print(t2);
    }

    {
        Base base{default_x, default_y};  // target

        auto tlist = With::Name | With::Health | With::Protection | With::Damage;

        // auto tp = Base{default_x, default_y} | tlist;
        auto tp = base | tlist;  // modify existing target type

        // update rest of target parameters
        auto update = [](auto& target) {
            return [&target]<typename... Args>
                requires(
                    (std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>) and  // every argument have unique type
                    (trait<std::remove_cvref_t<Args>>::template accessable<std::remove_cvref_t<decltype(target)>> and ...))             // every type is accessable by trait
            (Args&&... args) {
                ((trait<std::remove_cvref_t<Args>>::get(target) = std::forward<Args>(args)), ...);
            };
        };

        int default_int = 100;
        // constexpr int default_int = 100;

        update(tp)(
            Health{100, 100},
            float{3.14f},  // type<float>
            // int{100},       // type<int>
            default_int,    // type<int>
            double{20.20},  // type<double>
            Damage{5, DamageType::Divine},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        print(tp);
    }

    {                              // extra example
        list tlist2 = With::Name;  // ? implicit conversion needed (don't use auto)
        auto tlist3 = With::Name;  // !

        auto tp2 = Base{default_x, default_y} | tlist2;
        auto tp3 = Base{default_x, default_y} | tlist3;  // ! creator

        std::cout << '\n';
        std::cout << "tp2 =    " << name<decltype(tp2)>() << '\n';
        std::cout << "tp3 =    " << name<decltype(tp3)>() << '\n';  // ! creator
        std::cout << '\n';
    }
}
