#undef NO_PREMADE_PROPERTIES
// #define NO_PREMADE_PROPERTIES

#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Usage/With.hpp"

#include "type1.hpp"
#include "type2.hpp"
struct Empty {};
#include "type3.hpp"
#include "type4.hpp"
#include "type5.hpp"

#include "example1.hpp"
#include "example2.hpp"
#include "example3.hpp"

int main() {
    {  // 1 way of access
        static_assert(trait_accessable<Type1, Name>);
        Type1 type_1{};
        std::cout << "access 1  = " << type_1.name << '\n'
                  << '\n';
    }
    {  // 2 way of access
        static_assert(trait_accessable<Type2, Name>);
        Type2 type_2{};
        std::cout << "access 2  = " << type_2.getName() << '\n'
                  << '\n';
    };
    {  // 3 way of access
        static_assert(trait_accessable<decltype(type_3), Damage>);
        trait<Damage>::get(type_3) = Damage{5};
#ifndef NO_PREMADE_PROPERTIES
        std::cout << "access 3a = " << type_3.getDamage() << '\n'
                  << '\n';
#else
        std::cout << "access 3b = " << type_3.getType() << '\n'
                  << '\n';
#endif
    }
    {  // 4 way of access
        static_assert(trait_accessable<decltype(type_4), std::string>);
        static_assert(trait_accessable<decltype(type_4), int>);
        trait<std::string>::get(type_4) = "Type4";
        type_4.getType<std::string, 1>() = "Type4-2";

        std::cout << "access 4a = " << type_4.getType() << '\n';  // closest getType implementation
        std::cout << "access 4b = " << type_4.getType<std::string>() << '\n';
        std::cout << "access 4c = " << type_4.getType<int>() << '\n';
        std::cout << "access 4d = " << type_4.getType<std::string, 1>() << '\n';                       // second std::string getter
        std::cout << "access 4e = " << type_4.getTypeTaged<std::string, Empty>() << '\n';              // second std::string getter
        std::cout << "access 4f = " << type_4.getTypeOfSignature<list<std::string, Empty>>() << '\n';  // second std::string getter
        std::cout << "access 4g = " << type_4.getTaged<Empty>() << '\n'                                // second std::string getter
                  << '\n';
    }
    {  // 5 way of access
        auto type_5 = Type5{} | With::Damage | Create;
        static_assert(trait_accessable<decltype(type_5), Name>);
        static_assert(trait_accessable<decltype(type_5), Damage>);
        traits::CustomAccessType<Name, std::remove_cvref_t<decltype(type_5)>>::get(type_5) = Name{"type 5"};
        std::cout << "access 5  = " << traits::CustomAccessType<Name, std::remove_cvref_t<decltype(type_5)>>::get(type_5) << '\n'
                  << '\n';
    }
    {  // examples of CustomAccessType
        CustomName_1 type1{};
        CustomName_2 type2{};
        CustomName_3 type3{};

        static_assert(trait_accessable<decltype(type1), Name>);
        static_assert(trait_accessable<decltype(type2), Name>);
        static_assert(trait_accessable<decltype(type3), Name>);

        trait<Name>::get(type1) = Name{"test1"};
        trait<Name>::get(type2) = Name{"test2"};
        trait<Name>::get(type3) = Name{"test3"};  // will not change value

        type1.other = Name{"test1"};
        type2.name() = Name{"test2"};
        type3.name() = Name{"test3"};  // will not change value

        auto value_1 = trait<Name>::get(type1);
        auto value_2 = trait<Name>::get(type2);
        auto value_3 = trait<Name>::get(type3);

        std::cout << "example 1 = " << value_1 << '\n';
        std::cout << "example 2 = " << value_2 << '\n';
        std::cout << "example 3 = " << value_3 << '\n'
                  << '\n';
    }
}
