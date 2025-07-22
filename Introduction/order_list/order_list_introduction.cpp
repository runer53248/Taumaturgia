#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Introduction/order_list/order_list.hpp"

#include <iostream>
#include "Introduction/parse_type_name.hpp"

struct Base {};

struct AccessInt {
    template <size_t S>
    static constexpr decltype(auto) get(auto& el) {
        return (el.template getType<int, S>());
    }
};

int main() {
    auto type =
        Base{}                                                //
        | With::user_property<int, struct second_int>         //* 6  : not in list
        | Property<int_second_tag::apply>{}                    //  1  :
        | Property<int_second_tag::once>{}                    //  1  :
        | Property<int_third::once>{}                         //  2  :
        | Property<int_first::once>{}                         //  0  :
        | With::user_property<int, struct second_int>         //* 6  : not in list
        | Property<just_float::once>{}                        //  3  :
        | Property<string_second::apply>{}                     //  5  :
        | Property<string_first::apply>{}                      //  4  :
        | With::user_property_once<bool, struct first_bool>   //* 7  : not in list
        | With::user_property_once<bool, struct second_bool>  //* 8  : not in list
        | With::user_property<char, struct first_char>        //* 9  : not in list
        | With::user_property<char, struct second_char>       //* 10 : not in list
        | With::user_property<float>                          //  3  :
        | Property<string_first::apply>{}                      //  4  :
        | Property<int_third::once>{}                         //  2  :
        | With::Damage                                        //* 11 : not in list
        | Create;

    std::cout << "decltype(type) " << parse_type_name<decltype(type)>() << '\n';

    AccessInt::get<0>(type) = 100;
    AccessInt::get<1>(type) = 200;
    AccessInt::get<2>(type) = 300;
    AccessInt::get<3>(type) = 400;

    std::cout << "getTypeTaged<int, first_int>           = " << type.getTypeTaged<int, first_int>() << '\n';
    std::cout << "getTypeTaged<int, second_int, int_tag> = " << type.getTypeTaged<int, second_int, int_tag>() << '\n';
    std::cout << "getTypeTaged<int, third_int>           = " << type.getTypeTaged<int, third_int>() << '\n';
    std::cout << "getTypeTaged<int, second_int>          = " << type.getTypeTaged<int, second_int>() << '\n';
    std::cout << '\n';

    std::cout << "getType<int, 0>  = " << type.getType<int, 1>() << '\n';
    std::cout << "getType<int, 1>  = " << type.getType<int, 1>() << '\n';
    std::cout << "getType<int, 2>  = " << type.getType<int, 2>() << '\n';
    std::cout << "getType<int, 3>  = " << type.getType<int, 3>() << '\n';
    std::cout << '\n';

    using Type = decltype(type);
    Type type2{
        5,
        10,
        15,
        3.2f,
        "text",
        "title",
        20,
        true,
        false,
        'a',
        'b',
        Damage{100}};

    std::cout << "int 0       " << type2.getType<int, 0>() << '\n';
    std::cout << "int 1       " << type2.getType<int, 1>() << '\n';
    std::cout << "int 2       " << type2.getType<int, 2>() << '\n';
    std::cout << "int 3       " << type2.getType<int, 3>() << '\n';
    std::cout << "float       " << type2.getType<float>() << '\n';
    std::cout << "string 0    " << type2.getType<std::string, 0>() << '\n';
    std::cout << "string 1    " << type2.getType<std::string, 1>() << '\n';
    std::cout << "bool 0      " << type2.getType<bool, 0>() << '\n';
    std::cout << "bool 1      " << type2.getType<bool, 1>() << '\n';
    std::cout << "char 0      " << type2.getType<char, 0>() << '\n';
    std::cout << "char 1      " << type2.getType<char, 1>() << '\n';
    std::cout << "Damage      " << type2.getType<Damage>() << '\n';
    std::cout << '\n';

    std::cout << "trait<int>    " << trait<int>::get(type2) << '\n';
    std::cout << "trait<float>  " << trait<float>::get(type2) << '\n';
    std::cout << "trait<string> " << trait<std::string>::get(type2) << '\n';
    std::cout << "trait<bool>   " << trait<bool>::get(type2) << '\n';
    std::cout << "trait<char>   " << trait<char>::get(type2) << '\n';
    std::cout << "trait<Damage> " << trait<Damage>::get(type2) << '\n';
    std::cout << '\n';

    {
        static_assert(not helpers::impl::same_priority<
                      Property<int_second_tag::apply>,
                      Property<int_third::apply>>::value);

        static_assert(Property<int_first::apply>::value == Property<int_first::once>::value);
        static_assert(Property<int_second_tag::apply>::value == Property<int_second_tag::once>::value);
        static_assert(Property<int_third::apply>::value == Property<int_third::once>::value);

        std::cout << "priority of int_first::apply      = " << Property<int_first::apply>::value << '\n';
        std::cout << "priority of int_second_tag::apply = " << Property<int_second_tag::apply>::value << '\n';
        std::cout << "priority of int_third::apply      = " << Property<int_third::apply>::value << '\n';
        std::cout << "priority of just_float::once     = " << Property<just_float::once>::value << '\n';
        std::cout << '\n';

        using Type2 = add_properties_ordered<Base,
                                             int_second_tag::apply,
                                             int_third::apply,
                                             just_float::once,
                                             int_first::apply>;
        using Type3 = add_properties_ordered<Base,
                                             just_float::once,
                                             int_third::apply,
                                             int_second_tag::apply>;

        using Type4 = add_properties_ordered<Base,
                                             int_second_tag::apply,
                                             int_third::apply>;

        std::cout << "Type2 " << parse_type_name<Type2>() << '\n';
        std::cout << "Type3 " << parse_type_name<Type3>() << '\n';
        std::cout << "Type4 " << parse_type_name<Type4>() << '\n';
        std::cout << '\n';
    }
}
