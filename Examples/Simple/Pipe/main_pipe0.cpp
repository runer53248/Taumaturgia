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

// MARK: main

int main() {
    auto print = [](auto type_simple, int id) {
        auto type_name = "type simple" + std::to_string(id);
        std::cout << type_name << "       = " << name<decltype(type_simple)>() << '\n';
        if constexpr (trait<float>::accessable<decltype(type_simple)>)
            std::cout << type_name << " float = " << trait<float>::get(type_simple) << '\n';
        if constexpr (trait<Damage>::accessable<decltype(type_simple)>)
            std::cout << type_name << " dmg   = " << trait<Damage>::get(type_simple) << '\n';
        if constexpr (trait<int>::accessable<decltype(type_simple)>)
            std::cout << type_name << " int   = " << trait<int>::get(type_simple) << '\n';
        std::cout << '\n';
    };

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
        print(type_simple0, 0);
    }

    {
        struct Simple1 {} simple1{};

        auto create_type_simple1 =
            simple1         //
            | With::Damage  //
            ;
        auto type_simple1 = create_type_simple1();
        type_simple1 = create_type_simple1(Damage{2});
        print(type_simple1, 1);
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
        print(type_simple2, 2);
    }

    {
        Simple3 simple3{};
        auto create_type_simple3 =
            simple3                       //
            | With::user_property<float>  //
            | With::Damage  //
            ;
        decltype(create_type_simple3)::result_type type_simple3;
        type_simple3 = create_type_simple3();
        type_simple3 = create_type_simple3(8.8f);
        type_simple3 = create_type_simple3(std::ignore, Damage{13, DamageType::Magical});
        print(type_simple3, 3);
    }
}
