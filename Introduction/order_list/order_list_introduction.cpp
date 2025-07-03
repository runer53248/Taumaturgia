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
        | Property<int_second_tag::type>{}                    //  1  :
        | Property<int_second_tag::order>{}                   //  1  :
        | Property<int_third::order>{}                        //  2  :
        | Property<int_first::order>{}                        //  0  :
        | With::user_property<int, struct second_int>         //* 6  : not in list
        | Property<just_float::type>{}                        //  3  :
        | Property<string_second::type>{}                     //  5  :
        | Property<string_first::type>{}                      //  4  :
        | With::user_property_once<bool, struct first_bool>   //* 7  : not in list
        | With::user_property_once<bool, struct second_bool>  //* 8  : not in list
        | With::user_property<char, struct first_char>        //* 9  : not in list
        | With::user_property<char, struct second_char>       //* 10 : not in list
        | With::user_property<float>                          //  3  :
        | Property<string_first::type>{}                      //  4  :
        | Property<int_third::order>{}                        //  2  :
        | With::Damage                                        //* 11 : not in list
        | Create;

    std::cout << "decltype(type) " << parse_type_name<decltype(type)>() << '\n';

    AccessInt::get<0>(type) = 100;
    AccessInt::get<1>(type) = 200;
    std::cout << type.getType<int, 0>() << '\n';
    std::cout << type.getType<int, 1>() << '\n';
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

    std::cout << "Type1 " << parse_type_name<decltype(type)>() << '\n';
    std::cout << '\n';

    static_assert(not helpers::impl::same_priority<
                  Property<int_second_tag::type>,
                  Property<int_third::type>>::value);

    using Type2 = add_properties_ordered<Base,
                                         int_second_tag::type,
                                         int_third::type,
                                         just_float::type,
                                         int_first::type>;
    using Type3 = add_properties_ordered<Base,
                                         just_float::type,
                                         int_third::type,
                                         int_second_tag::type>;

    std::cout << "Type2 " << parse_type_name<Type2>() << '\n';
    std::cout << "Type3 " << parse_type_name<Type3>() << '\n';
    std::cout << '\n';

    std::cout << "add_properties_ordered<Base, int_second_tag, int_third> "
              << parse_type_name<add_properties_ordered<Base,
                                                        int_second_tag::type,
                                                        int_third::type>>()
              << '\n';

    static_assert(Property<int_first::type>::value == Property<int_first::order>::value);
    static_assert(Property<int_second_tag::type>::value == Property<int_second_tag::order>::value);
    static_assert(Property<int_third::type>::value == Property<int_third::order>::value);

    std::cout << Property<int_first::type>::value << '\n';
    std::cout << Property<int_second_tag::type>::value << '\n';
    std::cout << Property<int_third::type>::value << '\n';
    std::cout << Property<just_float::type>::value << '\n';
    std::cout << '\n';

    Type2 t2{};

    constexpr int int_value_0 = 100;
    constexpr int int_value_1 = 200;
    constexpr int int_value_2 = 300;

    t2.getType<int>() = int_value_0;
    t2.getType<int, 1>() = int_value_1;
    t2.getType<int, 2>() = int_value_2;

    std::cout << (t2.getType<int>() == int_value_0) << '\n';
    std::cout << (t2.getType<int, 1>() == int_value_1) << '\n';
    std::cout << (t2.getType<int, 2>() == int_value_2) << '\n';
}
