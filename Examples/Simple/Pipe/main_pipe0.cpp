// #define IGNORE_ORDER_LIST

#define CUSTOM_ORDER_LIST
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

int main() {
    struct Simple {
        Damage dmg{};
    } simple{};

    auto create_type_simple =
        simple          //
        | With::Damage  //
        ;
    auto type_simple = create_type_simple();
    type_simple = create_type_simple(Damage{});
    std::cout << "type simple   = " << name<decltype(type_simple)>() << '\n';

    struct Simple2 {
        Simple2(int) {}
    } simple2{5};

    auto create_object =
        simple2                                             //
        // | With::property<UserPropertyAdapter<float>::type>  //
        | With::user_property<float>  //
        ;
    auto type_object = create_object(
        std::ignore,
        5);
    type_object = create_object(
        11.11f,
        5);

    std::cout << "type obj     = " << name<decltype(type_object)>() << '\n';
    std::cout << "float      = " << trait<float>::get(type_object) << '\n';
}
