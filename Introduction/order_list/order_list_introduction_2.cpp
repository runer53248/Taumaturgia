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
        static_assert(
            std::is_same_v<
                decltype(With::user_property<int, struct first_int>),
                const Property<int_first::type>>);

        std::cout << "order index: \n";
        std::cout << "higher on order_list " << decltype(With::user_property<int, struct first_int>)::value << '\n';
        std::cout << "lower on order_list  " << decltype(With::user_property<float>)::value << '\n';
        std::cout << "not on order_list    " << decltype(With::user_property<bool>)::value << '\n';
        std::cout << '\n';
    }
    {
        // type build with property list
        [[maybe_unused]] list list_1 =                                // * takes all unique types and order them
            With::Name                                                // 6  : Name / impl::Naming_
            | With::user_property<bool, bool>                         // 7  : bool
            | With::user_property<char, bool, bool>                   // 8  : char
            | With::user_property<float>                              // 3  : float - (aka. f_p_t)
            | With::user_property<float, float, int>                  // 9  : float
            | With::Damage                                            // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                // 11 : int
            | With::user_property<int, struct first_int>              // 2  : int - (aka. i_p1::type)
            | With::user_property<std::string, struct first_string>   // 4  : string - (aka. i_p1::type)
            | With::user_property<std::string, struct second_string>  // 5  : string - (aka. i_p2::type)
            | With::user_property<double, struct second_double>       // 0  : double - (aka. d_p2::type)
            | With::user_property<double, struct first_double>        // 1  : double - (aka. d_p1::type)
            | With::user_property<Damage, struct Damage_first>        // 12 : Damage added
            | With::taged_property<Damaging, struct Damage_first>     // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging>                          // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type1 = Base{} | list_1;

        // types build with impl::DataAndPropertiesList and Create
        auto type2 =
            Base{}                                                    // * takes all unique types and order them
            | With::Name                                              // 6 : Name / impl::Naming_
            | With::user_property<bool, bool>                         // 7  : bool
            | With::user_property<char, bool, bool>                   // 8  : char
            | With::user_property<float>                              // 3  : float - because its on order_list (aka. f_p_t)
            | With::user_property<float, float, int>                  // 9  : float
            | With::Damage                                            // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                // 11 : int
            | With::user_property<int, struct first_int>              // 2  : int - because its on order_list (aka. i_p1::type)
            | With::user_property<std::string, struct first_string>   // 4  : string - because its on order_list (aka. i_p1::type)
            | With::user_property<std::string, struct second_string>  // 5  : string - because its on order_list (aka. i_p2::type)
            | With::user_property<double, struct second_double>       // 0  : double - because its on order_list (aka. d_p2::type)
            | With::user_property<double, struct first_double>        // 1  : double - because its on order_list (aka. d_p1::type)
            | With::user_property<Damage, struct Damage_first>        // 12 : Damage added
            | With::taged_property<Damaging, struct Damage_first>     // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging>                          // !  : Damage / impl::Damaging_ - duplication
            | Create;

        // types build with creator
        auto type3_creator =
            From::base<Base>                                          // * takes all unique types and order them
            | With::Name                                              // 6 : Name / impl::Naming_
            | With::user_property<bool, bool>                         // 7  : bool
            | With::user_property<char, bool, bool>                   // 8  : char
            | With::user_property<float>                              // 3  : float - because its on order_list (aka. f_p_t)
            | With::user_property<float, float, int>                  // 9  : float
            | With::Damage                                            // 10 : Damage / impl::Damaging_
            | With::user_property<int>                                // 11 : int
            | With::user_property<int, struct first_int>              // 2  : int - because its on order_list (aka. i_p1::type)
            | With::user_property<std::string, struct first_string>   // 4  : string - because its on order_list (aka. i_p1::type)
            | With::user_property<std::string, struct second_string>  // 5  : string - because its on order_list (aka. i_p2::type)
            | With::user_property<double, struct second_double>       // 0  : double - because its on order_list (aka. d_p2::type)
            | With::user_property<double, struct first_double>        // 1  : double - because its on order_list (aka. d_p1::type)
            | With::user_property<Damage, struct Damage_first>        // 12 : Damage added
            | With::taged_property<Damaging, struct Damage_first>     // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | With::taged_property<Damaging>                          // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type3 = type3_creator();

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
            std::cout << "3  = " << decltype(With::taged_property<Damaging>)::value << '\n';
            std::cout << "4  = " << decltype(With::taged_property<Damaging, struct Damage_first>)::value << '\n';
            std::cout << "1  = " << name<decltype(With::user_property<Damage, struct Damage_first>)>() << '\n';
            std::cout << "2  = " << name<decltype(With::Damage)>() << '\n';
            std::cout << "3  = " << name<decltype(With::taged_property<Damaging>)>() << '\n';
            std::cout << "4  = " << name<decltype(With::taged_property<Damaging, struct Damage_first>)>() << '\n';

            std::cout << "decltype(1) " << name<decltype(t1_creator)>() << '\n';
            std::cout << "decltype(2) " << name<decltype(t2_creator)>() << '\n';
            std::cout << "decltype(3) " << name<decltype(t3_creator)>() << '\n';
            std::cout << "decltype(1) " << parse_type_name<decltype(type1)>() << '\n';
            std::cout << "decltype(2) " << parse_type_name<decltype(type2)>() << '\n';
            std::cout << "decltype(3) " << parse_type_name<decltype(type3)>() << '\n';
        }

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
            With::user_property<Damage, struct Damage_first> | With::user_property<Damage>;
        [[maybe_unused]] list list_2 =
            With::taged_property<Damaging, struct Damage_first> | With::taged_property<Damaging>;

        auto type_test_1 = Base{} | list_1;
        auto type_test_2 = Base{} | list_2;

        std::cout << "decltype(type_test_1) " << parse_type_name<decltype(type_test_1)>() << '\n';
        std::cout << "decltype(type_test_2) " << parse_type_name<decltype(type_test_2)>() << '\n';
    }

    {
        auto prop_1 = With::taged_property_once<Damaging, struct Damage_first>;
        auto prop_2 = With::taged_property_once<Damaging>;
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

        std::cout << "decltype(l_test_a) " << name<decltype(l_test_a)>() << '\n'
                  << '\n';
        std::cout << "decltype(l_test_b) " << name<decltype(l_test_b)>() << '\n'
                  << '\n';
        std::cout << "decltype(l_test_c) " << name<decltype(l_test_c)>() << '\n'
                  << '\n';

        auto type_test_a = Base{} | l_test_a;
        auto type_test_b = Base{} | l_test_b;
        auto type_test_c = Base{} | l_test_c;

        std::cout << "decltype(type_test_a) " << parse_type_name<decltype(type_test_a)>() << '\n';
        std::cout << "decltype(type_test_b) " << parse_type_name<decltype(type_test_b)>() << '\n';
        std::cout << "decltype(type_test_c) " << parse_type_name<decltype(type_test_c)>() << '\n';
    }

    if (false) {
        // goes with order
        // ! accept only properties with higher order index

        // type build with property list
        [[maybe_unused]] list l_p2 =                                       //
            With::Name_once                                                // 2 : Name / impl::Naming_
            | With::user_property_once<bool, bool>                         // ! : bool
            | With::user_property_once<bool, struct other_bool>            // 3 : bool
            | With::user_property_once<char, bool, bool>                   // 4 : char
            | With::user_property_once<float>                              // ! : float - (aka. f_p_t)
            | With::user_property_once<float, float, int>                  // 5 : float
            | With::Damage_once                                            // ! : Damage / impl::Damaging_
            | With::user_property_once<int>                                // 6 : int
            | With::user_property_once<int, struct first_int>              // ! : int - (aka. i_p1::type)
            | With::user_property_once<std::string, struct first_string>   // ! : string - (aka. i_p1::type)
            | With::user_property_once<std::string, struct second_string>  // 1 : string - (aka. i_p2::type)
            | With::user_property_once<double, struct second_double>       // 0 : double - (aka. d_p2::type)
            | With::user_property_once<double, struct first_double>        // ! : double - (aka. d_p1::type)
            | With::taged_property_once<Damaging, struct Damage_first>     // 7 : Damage / impl::Damaging_
            | With::taged_property_once<Damaging>                          // ! : Damage / impl::Damaging_ - duplication
            | With::user_property_once<Damage, struct Damage_first>        // 7 : Damage - replace impl::Damaging_
            ;
        auto type2 = Base{} | l_p2;

        // With::user_property_once takes AdvanceUserProperty::order with checking for existing type property

        // types build with impl::DataAndPropertiesList and Create
        auto type00 =
            Base{}                                                         // * takes these with higher order index (last unordered or last in order)
            | With::Name_once                                              // 2  : Name / impl::Naming_
            | With::user_property_once<bool, bool>                         // ! : bool
            | With::user_property_once<bool, struct other_bool>            // 3 : bool
            | With::user_property_once<char, bool, bool>                   // 4 : char
            | With::user_property_once<float>                              // ! : float - ignored (aka. f_p_t)
            | With::user_property_once<float, float, int>                  // 5 : float - higher index as unordered
            | With::Damage_once                                            // ! : Damage / impl::Damaging_
            | With::user_property_once<int>                                // 6 : int - higher index as unordered
            | With::user_property_once<int, struct first_int>              // ! : int - ignored (aka. i_p1::order)
            | With::user_property_once<std::string, struct first_string>   // ! : string - ignored (aka. s_p1::order)
            | With::user_property_once<std::string, struct second_string>  // 1 : string - higher index for std::string (aka. s_p2::order)
            | With::user_property_once<double, struct second_double>       // 0 : double - higher index for double (aka. d_p2::order)
            | With::user_property_once<double, struct first_double>        // ! : double - ignored (aka. d_p1::order)
            | With::taged_property_once<Damaging, struct Damage_first>     // 7 : Damage / impl::Damaging_
            | With::taged_property_once<Damaging>                          // ! : Damage / impl::Damaging_ - duplication
            | With::user_property_once<Damage, struct Damage_first>        // 7 : Damage - replace impl::Damaging_
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
