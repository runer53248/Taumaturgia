// #define IGNORE_ORDER_LIST

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
    struct Example {
        auto getFloat(size_t index = 0) { return f_[index % 2]; }

    private:
        std::array<float, 2> f_{3.1113f, 0.5f};
    };

    auto create_type_2 =
        From::base<Example>                 //
        | With::Damage                      //
        | With::Name                        //
        | With::Protection                  //
        | With::Protection                  //
        | With::property<Protecting>        //
        | With::Health                      // not in priority order
        | With::user_property<int>          //
        | With::user_property<std::string>  //
        ;
#ifdef IGNORE_ORDER_LIST
    auto type_2 = create_type_2(  // ordered as given
        Damage{5, DamageType::Physical},
        Name{"Type 2"},
        Protection{10, BodyLocation::Legs},
        Health{300, 300},
        15,
        std::string{"test string"});
#else
    auto type_2 = create_type_2(  // ordered as property priority
        Name{"Type 2"},
        Health{300, 300},
        Damage{5, DamageType::Physical},
        Protection{10, BodyLocation::Legs},
        15,  // order of string and int same as given (not based on order_list property value)
        std::string{"test string"});
#endif
    type_2 = create_type_2(
        unordered,  // order ignored
        15,
        Protection{10, BodyLocation::Legs},
        std::string{"test string"},
        Damage{5, DamageType::Physical},
        Health{300, 300},
        Name{"Type 2"});

    std::cout << "create_type= " << name<decltype(create_type_2)>() << '\n'
              << '\n';

    std::cout << '\n';
    std::cout << "type       = " << name<decltype(type_2)>() << '\n';
    std::cout << "Name       = " << trait<Name>::get(type_2) << '\n';
    std::cout << "Health     = " << trait<Health>::get(type_2) << '\n';
    std::cout << "Damage     = " << trait<Damage>::get(type_2) << '\n';
    std::cout << "Protection = " << trait<Protection>::get(type_2) << '\n';
    std::cout << "int        = " << trait<int>::get(type_2) << '\n';
    std::cout << "string     = " << trait<std::string>::get(type_2) << '\n';

    std::cout << "float acces= " << trait<float>::accessable<decltype(type_2)> << '\n';

#ifndef NO_PREMADE_PROPERTIES
    std::cout << "Name       = " << type_2.getName() << '\n';
    std::cout << "Health     = " << type_2.getHealth() << '\n';
    std::cout << "Damage     = " << type_2.getDamage() << '\n';
    std::cout << "Protection = " << type_2.getProtection() << '\n';
#else
    std::cout << "Name       = " << type_2.getType<Name>() << '\n';
    std::cout << "Health     = " << type_2.getType<Health>() << '\n';
    std::cout << "Damage     = " << type_2.getType<Damage>() << '\n';
    std::cout << "Protection = " << type_2.getType<Protection>() << '\n';
#endif
    std::cout << "int        = " << type_2.getType<int>() << '\n';
    std::cout << "string     = " << type_2.getType<std::string>() << '\n';
    std::cout << "float 0    = " << type_2.getFloat(0) << '\n';
    std::cout << "float 1    = " << type_2.getFloat(1) << '\n';
}
