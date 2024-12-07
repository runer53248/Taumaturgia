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
    Simple3(Damage dmg)
        : dmg{dmg} {}

    decltype(auto) Dmg(this auto& self) { return (self.dmg); }
    decltype(auto) Int(this auto& self) { return (self.i); }

private:
    Damage dmg{5};
    int i{3};
};

template <typename T>
concept Simplelike = requires(T t) {
    { t.Dmg() };
    { t.Int() };
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
    auto print = []<typename Type>(const Type& type, int id) {
        auto type_name = "type simple" + std::to_string(id);
        std::cout << type_name << "       = " << name<Type>() << '\n';
        if constexpr (trait_accessable<Type, Name>)
            std::cout << type_name << " Name  = " << trait<Name>::get(type) << '\n';
        if constexpr (trait_accessable<Type, float>)
            std::cout << type_name << " float = " << trait<float>::get(type) << '\n';
        if constexpr (trait_accessable<Type, Health>)
            std::cout << type_name << " health= " << trait<Health>::get(type) << '\n';
        if constexpr (trait_accessable<Type, Damage>)
            std::cout << type_name << " dmg   = " << trait<Damage>::get(type) << '\n';
        if constexpr (trait_accessable<Type, int>)
            std::cout << type_name << " int   = " << trait<int>::get(type) << '\n';
        std::cout << '\n';
    };

    {
        struct Simple0 {
            Damage dmg{};
        };

        auto create_type_simple0 =
            From::base<Simple0>  //
            | With::Damage       //
            ;
        auto type_simple0 = create_type_simple0();
        type_simple0 = create_type_simple0(Damage{1});
        print(type_simple0, 0);
    }

    {
        struct Simple00 {};

        using T = Damaging<Living<Simple00>>;
        static_assert(std::is_same_v<
                      impl::Creator<::add_properties<T, Property_unordered<Naming>>>,
                      impl::Creator<::add_properties_unordered<T, Naming>>>);
        static_assert(std::is_same_v<
                      impl::Creator<::add_properties<T, Property<Naming>>>,
                      impl::Creator<::add_properties_ordered<T, Naming>>>);
        using T2 = Living<Damaging<Simple00>>;
        static_assert(std::is_same_v<
                      impl::Creator<::add_properties<T2, Property_unordered<Naming>>>,
                      impl::Creator<::add_properties_unordered<T2, Naming>>>);
        static_assert(std::is_same_v<
                      impl::Creator<::add_properties<T2, Property<Naming>>>,
                      impl::Creator<::add_properties_ordered<T2, Naming>>>);

        auto create_type_simple00 =
            From::base<Simple00>                   //
            | WithUnordered::user_property<float>  //
            | WithUnordered::Damage                //
            | WithUnordered::Health                //
            | WithUnordered::Name                  //
            ;
        static_assert(std::is_same_v<
                      decltype(create_type_simple00)::result_type,
                      UserPropertyAdapter<float>::type<
                          Damaging<Living<Naming<Simple00>>>>>);
    }

    {
        struct Simple1 {};

        auto create_type_simple1 =
            From::base<Simple1>  //
            | With::Damage       //
            ;
        auto type_simple1 = create_type_simple1();
        type_simple1 = create_type_simple1(Damage{2});
        print(type_simple1, 1);
    }

    {
        struct Simple2 {
            Simple2(int v)
                : dmg{v}, i{v + 5} {}

            decltype(auto) Dmg() { return (dmg); }
            decltype(auto) Dmg() const { return (dmg); }

            decltype(auto) Int() { return (i); }
            decltype(auto) Int() const { return (i); }

        private:
            Damage dmg{5};
            int i{3};
        };

        auto create_type_simple2 =
            From::base<Simple2>           //
            | With::user_property<float>  //
            | With::Damage                //
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
        auto create_type_simple3 =
            From::base<Simple3>           //
            | With::user_property<float>  //
            | With::Damage                //
            ;
        decltype(create_type_simple3)::result_type type_simple3;
        type_simple3 = create_type_simple3();
        type_simple3 = create_type_simple3(8.8f);
        type_simple3 = create_type_simple3(std::ignore, Damage{13, DamageType::Magical});
        print(type_simple3, 3);
    }

    {
        struct Simple4 {};

        auto create_type_simple4_1 =
            From::base<Simple4>                    //
            | WithUnordered::user_property<float>  //
            | WithUnordered::Damage                //
            | WithUnordered::Health                //
            | WithUnordered::Name                  //
            ;
        auto create_type_simple4_2 =
            From::base<Simple4>                    //
            | With::Health                         //
            | WithUnordered::user_property<float>  //
            | WithUnordered::Name                  //
            | WithUnordered::Damage                //
            ;
        auto create_type_simple4_3 =
            From::base<Simple4>           //
            | With::user_property<float>  //
            | With::Damage                //
            | With::Health                //
            | With::Name                  //
            ;

        decltype(create_type_simple4_1)::result_type type_simple4_1;
        decltype(create_type_simple4_2)::result_type type_simple4_2;
        decltype(create_type_simple4_3)::result_type type_simple4_3;

        type_simple4_1 = create_type_simple4_1(
            3.14169f,
            Damage{9, DamageType::Physical},
            Health{41, 100},
            Name{"simple_4_1"});
        type_simple4_2 = create_type_simple4_2(
            Health{42, 100},
            3.14169f,
            Name{"simple_4_2"},
            Damage{9, DamageType::Magical});
        type_simple4_3 = create_type_simple4_3(
            Name{"simple_4_3"},
            Health{43, 100},
            Damage{9, DamageType::Divine},
            3.14169f);

        print(type_simple4_1, 41);
        print(type_simple4_2, 42);
        print(type_simple4_3, 43);
    }

    {
        struct Simple5 {};
        constexpr auto float_value = 50.01f;
        [[maybe_unused]] auto create_type_simple5 =
            From::base<Simple5>                    //
            | WithUnordered::user_property<float>  //
            | With::Damage                         // order everything to this point
            | WithUnordered::Health                // leave unordered
            ;
        auto type_simple5 = create_type_simple5(
            Damage{0, Effect{EffectType::Freeze}},
            float_value,
            Health{50, 100});
        print(type_simple5, 5);
    }
}
