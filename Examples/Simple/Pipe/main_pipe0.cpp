#define IGNORE_ORDER_LIST

// #define CUSTOM_ORDER_LIST
#include "custom_order_list.hpp"

#include "With.hpp"
#include "default_values.hpp"

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

struct Simple3 {
    Simple3() = default;
    Simple3(Damage dmg) : dmg{dmg} {}

    decltype(auto) Dmg(this auto& self) { return (self.dmg); }
    decltype(auto) Int(this auto& self) { return (self.i); }
private:
    Damage dmg{5};
    int i{3};
};

template <typename T>
concept Simplelike = requires (T t) {
    {t.Dmg()};
    {t.Int()};
};

template <Simplelike T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

template <Simplelike T>
struct traits::CustomAccessType<int, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Int();
    }
};

int main() {
    {
        struct Simple0 {
            Damage dmg{};
        } simple0{};

        auto create_type_simple0 =
            simple0         //
            | With::Damage  //
            ;
        auto type_simple0 = create_type_simple0();
        type_simple0 = create_type_simple0(Damage{1});
        std::cout << "type simple0       = " << name<decltype(type_simple0)>() << '\n';
        std::cout << "type simple0 dmg   = " << trait<Damage>::get(type_simple0) << '\n' << '\n';
    }

    {
        struct Simple1 {} simple1{};

        auto create_type_simple1 =
            simple1         //
            | With::Damage  //
            ;
        auto type_simple1 = create_type_simple1();
        type_simple1 = create_type_simple1(Damage{2});
        std::cout << "type simple1       = " << name<decltype(type_simple1)>() << '\n';
        std::cout << "type simple1 dmg   = " << trait<Damage>::get(type_simple1) << '\n' << '\n';
    }

    {
        struct Simple2 {
            Simple2(int v) : dmg{v}, i{v + 5} {}

            decltype(auto) Dmg() { return (dmg); }
            decltype(auto) Dmg() const { return (dmg); }
            
            decltype(auto) Int() { return (i); }
            decltype(auto) Int() const { return (i); }
        private:
            Damage dmg{5};
            int i{3};
        } simple2{5};

        auto create_type_simple2 =
            simple2                       //
            | With::user_property<float>  //
            | With::Damage  //
            ;
        auto type_simple2 = create_type_simple2(
            std::ignore,
            5);
        type_simple2 = create_type_simple2(
            11.11f,
            5);
        std::cout << "type simple2       = " << name<decltype(type_simple2)>() << '\n';
        std::cout << "type simple2 float = " << trait<float>::get(type_simple2) << '\n';
        std::cout << "type simple2 dmg   = " << trait<Damage>::get(type_simple2) << '\n';
        std::cout << "type simple2 int   = " << trait<int>::get(type_simple2) << '\n' << '\n';
    }

    {
        Simple3 simple3{};
        auto create_type_simple3 =
            simple3                       //
            | With::user_property<float>  //
            | With::Damage  //
            ;
        auto type_simple3 = create_type_simple3();
        type_simple3 = create_type_simple3(8.8f);
        type_simple3 = create_type_simple3(std::ignore, Damage{13, DamageType::Magical});
        std::cout << "type simple3       = " << name<decltype(type_simple3)>() << '\n';
        std::cout << "type simple3 float = " << trait<float>::get(type_simple3) << '\n';
        std::cout << "type simple3 dmg   = " << trait<Damage>::get(type_simple3) << '\n';
        std::cout << "type simple3 int   = " << trait<int>::get(type_simple3) << '\n' << '\n';
    }
}
