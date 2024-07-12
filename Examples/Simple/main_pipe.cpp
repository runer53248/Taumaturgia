#include <iostream>
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Usage/Strategies.hpp"

struct Base {};

struct Prop {
    static constexpr Property<Naming> Name{};
    static constexpr Property<Damaging> Damage{};
};

template <typename T, template <typename> typename Prop>
auto operator|(T, Property<Prop>) {
    return [](auto arg, auto... args) {
        if constexpr (std::invocable<T, decltype(arg)>) {
            using type = std::invoke_result_t<T, decltype(arg)>;
            return add_properties<type, Prop>(arg, args...);
        } else {
            using type = Prop<T>;
            return add_properties<type>(arg, args...);
        }
    };
}

template <template <typename> typename... P>
auto create = [](auto... args) {
    return add_properties<Base, P...>{args...};
};

int main() {
    auto t1 = add_properties<Base, Naming, Damaging>{Name{"Test"}, Damage{5}};
    auto t2 = Damaging<Naming<Base>>{Name{"Test"}, Damage{5}};

    auto create_type =
        Base{}        //
        | Prop::Name  //
        | Prop::Damage;
    auto t3 = create_type(Name{"Test"}, Damage{5});

    auto t4 = create<Naming, Damaging>(Name{"Test"}, Damage{5});

    std::cout << Namingable_trait::get(t1) << '\n';
    std::cout << Damagingable_trait::get(t1) << '\n';

    std::cout << Namingable_trait::get(t2) << '\n';
    std::cout << Damagingable_trait::get(t2) << '\n';

    std::cout << Namingable_trait::get(t3) << '\n';
    std::cout << Damagingable_trait::get(t3) << '\n';

    std::cout << Namingable_trait::get(t4) << '\n';
    std::cout << Damagingable_trait::get(t4) << '\n';
    std::cout << '\n';
}
