#include <iostream>

#define IGNORE_ORDER_LIST

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Strategies.hpp"

#include "Examples/demangle_type_name.hpp"

namespace With {
constexpr Property<Naming> Name{};
constexpr Property<Damaging> Damage{};
constexpr Property<Healing> CureHealth{};
constexpr Property<Living> Health{};
constexpr Property<Protecting> Protection{};
constexpr Property<Restoring> EffectTypeContainer{};
constexpr Property<Wearing> WearContainer{};
};  // namespace With

template <typename T, template <typename> typename Prop>
auto operator|(T, Property<Prop>) {
    return []<typename Arg, typename... Args>(Arg&& arg, Args&&... args) {
        if constexpr (std::invocable<T, Arg>) {
            using type = std::invoke_result_t<T, Arg>;
            return add_properties<type, Prop>(std::forward<Arg>(arg), std::forward<Args>(args)...);
        } else {
            using type = T;
            return add_properties<type, Prop>(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    };
}

struct Base {};

int main() {
    using type_1 = add_properties<Base, Damaging, Naming>;
    using type_2 = Damaging<Naming<Base>>;
    auto create_type_3 =
        Base{}              //
        | With::Name        //
        | With::Health      //
        | With::Damage      //
        | With::Protection  //
        ;

    auto t1 = type_1{
        Name{"Test"},
        Damage{5}};

    auto t2 = type_2{
        Name{"Test"},
        Damage{5}};

    auto t3 = create_type_3(
        Name{"Test"},
        Health{100, 100},
        Damage{5},
        Protection{10, BodyLocation::Head});

    std::cout << '\n';

    std::cout << name<decltype(t1)>() << '\n';
    std::cout << Namingable_trait::get(t1) << '\n';
    std::cout << Damagingable_trait::get(t1) << '\n';
    std::cout << '\n';

    std::cout << name<decltype(t2)>() << '\n';
    std::cout << Namingable_trait::get(t2) << '\n';
    std::cout << Damagingable_trait::get(t2) << '\n';
    std::cout << '\n';

    std::cout << name<decltype(t3)>() << '\n';
    std::cout << Namingable_trait::get(t3) << '\n';
    std::cout << Damagingable_trait::get(t3) << '\n';
    std::cout << Protectingable_trait::get(t3) << '\n';
    std::cout << Livingable_trait::get(t3) << '\n';
    std::cout << '\n';
}
