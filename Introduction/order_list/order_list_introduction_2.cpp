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
    {
        static_assert(std::is_same_v<
                      decltype(With::user_property<int, struct first_int>),
                      const Property<int_first::type>>);

        static_assert(Property<int_first::type>{} == With::user_property<int, struct first_int>);
        static_assert(Property<int_first::once>{} != With::user_property<int, struct first_int>);
        static_assert(Property<int_first::once>{} == With::user_property_once<int, struct first_int>);
        static_assert(Property<int_first::type>{} != With::user_property_once<int, struct first_int>);

        static_assert(Property<just_float::once>{} != With::user_property<float>);
        static_assert(Property<just_float::once>{} == With::user_property_once<float>);

        static_assert(Property_unordered<int_first::type>{} == WithUnordered::user_property<int, struct first_int>);
        static_assert(Property_unordered<int_first::once>{} != WithUnordered::user_property<int, struct first_int>);
        static_assert(Property_unordered<int_first::once>{} == WithUnordered::user_property_once<int, struct first_int>);
        static_assert(Property_unordered<int_first::type>{} != WithUnordered::user_property_once<int, struct first_int>);

        static_assert(Property_unordered<just_float::once>{} != WithUnordered::user_property<float>);
        static_assert(Property_unordered<just_float::once>{} == WithUnordered::user_property_once<float>);
    }

    {
        constexpr auto high_order_type_index = decltype(With::user_property<int, struct first_int>)::value;
        constexpr auto low_order_type_index = decltype(With::user_property<float>)::value;
        constexpr auto unorder_type_index = decltype(With::user_property<bool>)::value;

        static_assert(high_order_type_index < low_order_type_index);
        static_assert(low_order_type_index < unorder_type_index);

        std::cout << "order index: \n";
        std::cout << "higher on order_list " << high_order_type_index << '\n';
        std::cout << "lower on order_list  " << low_order_type_index << '\n';
        std::cout << "not on order_list    " << unorder_type_index << '\n';
        std::cout << '\n';
    }
    {
        auto t1_creator =
            From::base<Base>                                            //
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::taged_property<Damaging_impl, struct Damage_first>  //
            | With::taged_property<Damaging_impl>                       //
            | With::Damage                                              // ! last
            ;
        auto t2_creator =
            From::base<Base>                                            //
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::Damage                                              //
            | With::taged_property<Damaging_impl, struct Damage_first>  //
            | With::taged_property<Damaging_impl>                       // ! last
            ;
        auto t3_creator =
            From::base<Base>                                            //
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::Damage                                              //
            | With::taged_property<Damaging_impl>                       //
            | With::taged_property<Damaging_impl, struct Damage_first>  // ! last
            ;
        auto type1 = t1_creator();
        auto type2 = t2_creator();
        auto type3 = t3_creator();
        std::cout << "Damaging                  =  " << Property<Damaging>::value << '\n';
        std::cout << "Damaging<.. Damage_first> =  " << Property<Damaging<tag, struct Damage_first>::property_data::property_type::apply>::value << '\n';
        std::cout << "Damage                    =  " << Property<Damaging_impl>::value << '\n';
        std::cout << "Damage<.. Damage_first>   =  " << Property<Damaging_impl<tag, struct Damage_first>::property_data::property_type::apply>::value << '\n';
        std::cout << "1  = " << decltype(With::user_property<Damage, struct Damage_first>)::value << '\n';
        std::cout << "2  = " << decltype(With::Damage)::value << '\n';
        std::cout << "3  = " << decltype(With::taged_property<Damaging_impl>)::value << '\n';
        std::cout << "4  = " << decltype(With::taged_property<Damaging_impl, struct Damage_first>)::value << '\n';
        std::cout << "1  = " << name<decltype(With::user_property<Damage, struct Damage_first>)>() << '\n';
        std::cout << "2  = " << name<decltype(With::Damage)>() << '\n';
        std::cout << "3  = " << name<decltype(With::taged_property<Damaging_impl>)>() << '\n';
        std::cout << "4  = " << name<decltype(With::taged_property<Damaging_impl, struct Damage_first>)>() << '\n';

        std::cout << "decltype(1) " << name<decltype(t1_creator)>() << '\n';
        std::cout << "decltype(2) " << name<decltype(t2_creator)>() << '\n';
        std::cout << "decltype(3) " << name<decltype(t3_creator)>() << '\n';
        std::cout << "decltype(1) " << parse_type_name<decltype(type1)>() << '\n';
        std::cout << "decltype(2) " << parse_type_name<decltype(type2)>() << '\n';
        std::cout << "decltype(3) " << parse_type_name<decltype(type3)>() << '\n';
    }

    {
        // type build with property list
        [[maybe_unused]] list list_1 =                                  //
            With::Name                                                  // 6  : Name / impl::Naming_
            | With::user_property<bool, bool>                           // 7  : bool
            | With::user_property<char, bool, bool>                     // 8  : char
            | With::user_property<float>                                //*3  : float - (aka. just_float)
            | With::user_property<float, float, int>                    // 9  : float
            | With::Damage                                              // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                  // 11 : int
            | With::user_property<int, struct first_int>                //*2  : int - (aka. int_first::type)
            | With::user_property<std::string, struct first_string>     //*4  : string - (aka. string_first::type)
            | With::user_property<std::string, struct second_string>    //*5  : string - (aka. string_second::type)
            | With::user_property<double, struct second_double>         //*0  : double - (aka. double_second::type)
            | With::user_property<double, struct first_double>          //*1  : double - (aka. double_first::type)
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type1 = Base{} | list_1;

        // types build with impl::DataAndPropertiesList and Create
        auto type2 =
            Base{}                                                      //
            | With::Name                                                // 6  : Name / impl::Naming_
            | With::user_property<bool, bool>                           // 7  : bool
            | With::user_property<char, bool, bool>                     // 8  : char
            | With::user_property<float>                                //*3  : float - (aka. just_float)
            | With::user_property<float, float, int>                    // 9  : float
            | With::Damage                                              // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                  // 11 : int
            | With::user_property<int, struct first_int>                //*2  : int - (aka. int_first::type)
            | With::user_property<std::string, struct first_string>     //*4  : string - (aka. string_first::type)
            | With::user_property<std::string, struct second_string>    //*5  : string - (aka. string_second::type)
            | With::user_property<double, struct second_double>         //*0  : double - (aka. double_second::type)
            | With::user_property<double, struct first_double>          //*1  : double - (aka. double_first::type)
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            | Create;

        // types build with creator
        auto type3_creator =
            From::base<Base>                                            //
            | With::Name                                                // 6  : Name / impl::Naming_
            | With::user_property<bool, bool>                           // 7  : bool
            | With::user_property<char, bool, bool>                     // 8  : char
            | With::user_property<float>                                //*3  : float - (aka. just_float)
            | With::user_property<float, float, int>                    // 9  : float
            | With::Damage                                              // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                  // 11 : int
            | With::user_property<int, struct first_int>                //*2  : int - (aka. int_first::type)
            | With::user_property<std::string, struct first_string>     //*4  : string - (aka. string_first::type)
            | With::user_property<std::string, struct second_string>    //*5  : string - (aka. string_second::type)
            | With::user_property<double, struct second_double>         //*0  : double - (aka. double_second::type)
            | With::user_property<double, struct first_double>          //*1  : double - (aka. double_first::type)
            | With::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | With::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type3 = type3_creator();

        static_assert(std::same_as<decltype(type1), decltype(type2)>);
        // static_assert(std::same_as<decltype(type1), decltype(type3)>);

        if constexpr (std::same_as<decltype(type1), decltype(type2)>) {
            if constexpr (std::same_as<decltype(type1), decltype(type3)>) {
                std::cout << "decltype(type1) / decltype(type2) / decltype(type3) " << parse_type_name<decltype(type1)>() << '\n';
            } else {
                std::cout << "decltype(type1) / decltype(type2) " << parse_type_name<decltype(type1)>() << '\n';
                std::cout << "decltype(type3) " << parse_type_name<decltype(type3)>() << '\n';
            }
        } else {
            std::cout << "decltype(type1) " << parse_type_name<decltype(type1)>() << '\n';
            std::cout << "decltype(type2) " << parse_type_name<decltype(type2)>() << '\n';
            std::cout << "decltype(type3) " << parse_type_name<decltype(type3)>() << '\n';
        }
    }

    {
        [[maybe_unused]] list list_1 =
            With::user_property<Damage, struct Damage_first>  //
            | With::user_property<Damage>;
        [[maybe_unused]] list list_2 =
            With::taged_property<Damaging_impl, struct Damage_first>  //
            | With::taged_property<Damaging_impl>;

        auto type_test_1 = Base{} | list_1;
        auto type_test_2 = Base{} | list_2;

        std::cout << "1 ********************************* " << '\n'
                  << '\n';

        std::cout << "decltype(type_test_1) " << parse_type_name<decltype(type_test_1)>() << '\n';
        std::cout << "decltype(type_test_2) " << parse_type_name<decltype(type_test_2)>() << '\n';
    }

    {
        auto prop_1 = With::taged_property<Damaging_impl, struct Damage_first>;
        auto prop_2 = With::taged_property<Damaging_impl>;

        list l_test_a =  //
            prop_1       //
            | prop_2     //
            ;
        list l_test_b =  //
            prop_2       //
            | prop_1     //
            ;

        auto type_test_a = Base{} | l_test_a;
        auto type_test_b = Base{} | l_test_b;

        std::cout << "2 ********************************* " << '\n'
                  << '\n';

        std::cout << "decltype(type_test_a) " << parse_type_name<decltype(type_test_a)>() << '\n';
        std::cout << "decltype(type_test_b) " << parse_type_name<decltype(type_test_b)>() << '\n';
    }

    {
        auto prop_1 = With::taged_property<Damaging_impl, struct Damage_first>;
        auto prop_2 = With::taged_property<Damaging_impl>;
        auto prop_3 = With::user_property<Damage, struct Damage_first>;

        [[maybe_unused]] list l_test_a =  //
            prop_1                        //
            | prop_2                      //
            | prop_3                      //
            ;
        [[maybe_unused]] list l_test_b =  //
            prop_2                        //
            | prop_3                      //
            | prop_1                      //
            ;
        [[maybe_unused]] list l_test_c =  //
            prop_3                        //
            | prop_1                      //
            | prop_2                      //
            ;

        auto type_test_a = Base{} | l_test_a;
        auto type_test_b = Base{} | l_test_b;
        auto type_test_c = Base{} | l_test_c;

        std::cout << "3 ********************************* " << '\n'
                  << '\n';

        std::cout << "decltype(type_test_a) " << parse_type_name<decltype(type_test_a)>() << '\n';
        std::cout << "decltype(type_test_b) " << parse_type_name<decltype(type_test_b)>() << '\n';
        std::cout << "decltype(type_test_c) " << parse_type_name<decltype(type_test_c)>() << '\n';
    }

    {
        auto prop_1 = With::taged_property<Damaging_impl, struct Damage_first>;
        auto prop_2 = With::taged_property<Damaging_impl>;
        auto prop_3 = With::user_property_once<Damage, struct Damage_first>;

        [[maybe_unused]] list l_test_a =  //
            prop_1                        //
            | prop_2                      //
            | prop_3                      //
            ;
        [[maybe_unused]] list l_test_b =  //
            prop_2                        //
            | prop_3                      //
            | prop_1                      //
            ;
        [[maybe_unused]] list l_test_c =  //
            prop_3                        //
            | prop_1                      //
            | prop_2                      //
            ;

        auto type_test_a = Base{} | l_test_a;
        auto type_test_b = Base{} | l_test_b;
        auto type_test_c = Base{} | l_test_c;

        std::cout << "4 ********************************* " << '\n'
                  << '\n';

        std::cout << "decltype(type_test_a) " << parse_type_name<decltype(type_test_a)>() << '\n';
        std::cout << "decltype(type_test_b) " << parse_type_name<decltype(type_test_b)>() << '\n';
        std::cout << "decltype(type_test_c) " << parse_type_name<decltype(type_test_c)>() << '\n';
    }

    {
        // goes with order
        // ! accept only properties with higher order index

        // type build with property list
        [[maybe_unused]] list l_p2 =                                       //
            With::Name_once                                                // 6  : Name / impl::Naming_
            | With::user_property_once<bool, bool>                         // 7  : bool
            | With::user_property_once<bool, struct other_bool>            // 8  : bool
            | With::user_property_once<char, bool, bool>                   // 9  : char
            | With::user_property_once<float>                              //*3  : float - (aka. just_float)
            | With::user_property_once<float, float, int>                  // 10 : float
            | With::Damage_once                                            // 11 : Damage / impl::Damaging_
            | With::user_property_once<int>                                // 12 : int
            | With::user_property_once<int, struct first_int>              //*2  : int - (aka. int_first::type)
            | With::user_property_once<std::string, struct first_string>   //*4  : string - (aka. string_first::type)
            | With::user_property_once<std::string, struct second_string>  //*5  : string - (aka. string_second::type)
            | With::user_property_once<double, struct second_double>       //*1  : double - (aka. double_second::type)
            | With::user_property_once<double, struct first_double>        //*0  : double - (aka. double_first::type)
            | With::taged_property<Damaging_impl, struct Damage_first>     // 13 : Damage / impl::Damaging_
            | With::taged_property<Damaging_impl>                          // ! : Damage / impl::Damaging_ - duplication
            | With::user_property_once<Damage, struct Damage_first>        // 13 : Damage - replace impl::Damaging_
            ;
        auto type2 = Base{} | l_p2;

        // With::user_property_once takes AdvanceUserProperty::order with checking for existing type property

        // types build with impl::DataAndPropertiesList and Create
        auto type00 =
            Base{}                                                         //
            | With::Name_once                                              // 6  : Name / impl::Naming_
            | With::user_property_once<bool, bool>                         // 7  : bool
            | With::user_property_once<bool, struct other_bool>            // 8  : bool
            | With::user_property_once<char, bool, bool>                   // 9  : char
            | With::user_property_once<float>                              //*3  : float - (aka. just_float)
            | With::user_property_once<float, float, int>                  // 10 : float
            | With::Damage_once                                            // 11 : Damage / impl::Damaging_
            | With::user_property_once<int>                                // 12 : int
            | With::user_property_once<int, struct first_int>              //*2  : int - (aka. int_first::order)
            | With::user_property_once<std::string, struct first_string>   //*4  : string - (aka. string_first::order)
            | With::user_property_once<std::string, struct second_string>  //*5  : string - (aka. string_second::order)
            | With::user_property_once<double, struct second_double>       //*1  : double - (aka. double_second::order)
            | With::user_property_once<double, struct first_double>        //*0  : double - (aka. double_first::order)
            | With::taged_property<Damaging_impl, struct Damage_first>     // 13 : Damage / impl::Damaging_
            | With::taged_property<Damaging_impl>                          // !   : Damage / impl::Damaging_ - duplication
            | With::user_property_once<Damage, struct Damage_first>        // 13 : Damage - replace impl::Damaging_
            | Create;

        static_assert(std::same_as<decltype(type2), decltype(type00)>);

        if constexpr (std::same_as<decltype(type2), decltype(type00)>) {
            std::cout << "decltype(type2) / decltype(type00)  " << parse_type_name<decltype(type2)>() << '\n';
        } else {
            std::cout << "decltype(type2) " << parse_type_name<decltype(type2)>() << '\n';
            std::cout << "decltype(type00) " << parse_type_name<decltype(type00)>() << '\n';
        }

        std::cout << '\n';
    }

    return 0;
}
