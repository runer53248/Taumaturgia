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
        std::cout << "- *********** " << '\n';
        std::cout << "decltype(1) " << parse_type_name<add_properties<Base, Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>>>() << '\n';
        std::cout << "decltype(2) " << parse_type_name<add_properties<Base, Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>>>() << '\n';
        std::cout << "decltype(3) " << parse_type_name<add_properties<Base, Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>>>() << '\n';
        std::cout << "- *********** " << '\n'
                  << '\n';
    }

    {
        using test_type1 = add_properties<Base,
                                          Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>,
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<Damaging_impl>>;  // Damaging_impl
        using test_type2 = add_properties<Base,
                                          Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>>;

        using test_type3 = add_properties<Base,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>>;
        using test_type4 = add_properties<Base,
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>>;

        std::cout << "1 a ********************************* " << '\n'
                  << '\n';

        std::cout << "is duplicate taged Damage_first: " <<                                             //
            (Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>{}   //
             == Property_unordered<UserPropertyAdapter<Damage, struct Damage_first>::template once>{})  // ! later is not forced
                  << '\n'
                  << '\n';

        std::cout << "decltype(type1) " << parse_type_name<test_type1>() << '\n';
        std::cout << "decltype(type2) " << parse_type_name<test_type2>() << '\n';
        std::cout << "decltype(type3) " << parse_type_name<test_type3>() << '\n';
        std::cout << "decltype(type4) " << parse_type_name<test_type4>() << '\n';
    }

    {
        using test_type1 = add_properties<Base,
                                          Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>,
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<Damaging_impl>>;  // Damaging_impl
        using test_type2 = add_properties<Base,
                                          Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>>;

        using test_type3 = add_properties<Base,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>>;
        using test_type4 = add_properties<Base,
                                          Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>,
                                          Property_unordered<Damaging_impl>,  // Damaging_impl
                                          Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>>;

        std::cout << "1 b ********************************* " << '\n'
                  << '\n';

        std::cout << "is other duplicate taged Damage_first: " <<                                       //
            (Property_unordered<impl::ApplyTag<Damaging_impl, struct Damage_first>::template apply>{}   //
             == Property_unordered<AdvanceUserProperty<Damage, struct Damage_first>::template type>{})  // ? both are forced
                  << '\n'
                  << '\n';

        std::cout << "decltype(type1) " << parse_type_name<test_type1>() << '\n';
        std::cout << "decltype(type2) " << parse_type_name<test_type2>() << '\n';
        std::cout << "decltype(type3) " << parse_type_name<test_type3>() << '\n';
        std::cout << "decltype(type4) " << parse_type_name<test_type4>() << '\n';
    }

    {
        auto type_a =
            Base{}                                                               //
            | WithUnordered::Damage                                              //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //
            | WithUnordered::taged_property<Damaging_impl>                       //
            | Create;
        auto type_b =
            Base{}                                                               //
            | WithUnordered::taged_property<Damaging_impl>                       //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //
            | WithUnordered::Damage                                              //
            | Create;
        auto type_c =
            Base{}                                                               //
            | WithUnordered::Damage                                              //
            | WithUnordered::taged_property<Damaging_impl>                       //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //
            | Create;

        std::cout << "2 ********************************* " << '\n'
                  << '\n';

        std::cout << "is duplicate added: " <<  //
            (WithUnordered::Damage              //
             == WithUnordered::taged_property<Damaging_impl>)
                  << '\n'
                  << '\n';

        std::cout << "decltype(type_a) " << parse_type_name<decltype(type_a)>() << '\n';
        std::cout << "decltype(type_b) " << parse_type_name<decltype(type_b)>() << '\n';
        std::cout << "decltype(type_c) " << parse_type_name<decltype(type_c)>() << '\n';
    }

    {
        auto type_a =
            Base{}                                                               //
            | WithUnordered::Damage                                              //
            | WithUnordered::user_property<Damage, struct Damage_first>          //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //? sometimes duplicate
            | WithUnordered::taged_property<Damaging_impl>                       //! duplicate
            | Create;
        auto type_b =
            Base{}                                                               //
            | WithUnordered::taged_property<Damaging_impl>                       //
            | WithUnordered::user_property<Damage, struct Damage_first>          //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //? sometimes duplicate
            | WithUnordered::Damage                                              //! duplicate
            | Create;
        auto type_c =
            Base{}                                                               //
            | WithUnordered::Damage                                              //
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //
            | WithUnordered::user_property<Damage, struct Damage_first>          //? sometimes duplicate
            | WithUnordered::taged_property<Damaging_impl>                       //! duplicate
            | Create;

        std::cout << "3 ********************************* " << '\n'
                  << '\n';

        std::cout << "is duplicate taged Damage_first: " <<                     //
            (WithUnordered::taged_property<Damaging_impl, struct Damage_first>  //
             == WithUnordered::user_property<Damage, struct Damage_first>)
                  << '\n'
                  << '\n';

        std::cout << "decltype(type_a) " << parse_type_name<decltype(type_a)>() << '\n';
        std::cout << "decltype(type_b) " << parse_type_name<decltype(type_b)>() << '\n';
        std::cout << "decltype(type_c) " << parse_type_name<decltype(type_c)>() << '\n';
    }

    {
        // type build with property list
        [[maybe_unused]] list list_1 =                                           //
            WithUnordered::Name                                                  // 0  : Name / impl::Naming_
            | WithUnordered::user_property<bool, bool>                           // 1  : bool
            | WithUnordered::user_property<char, bool, bool>                     // 2  : char
            | WithUnordered::user_property<float>                                //*3  : float - (aka. just_float)
            | WithUnordered::user_property<float, float, int>                    // 4  : float
            | WithUnordered::Damage                                              // 5  : Damage / impl::Damaging_
            | WithUnordered::user_property<int>                                  // 6  : int
            | WithUnordered::user_property<int, struct first_int>                //*7  : int - (aka. int_first::type)
            | WithUnordered::user_property<std::string, struct first_string>     //*8  : string - (aka. string_first::type)
            | WithUnordered::user_property<std::string, struct second_string>    //*9  : string - (aka. string_second::type)
            | WithUnordered::user_property<double, struct second_double>         //*10 : double - (aka. double_second::type)
            | WithUnordered::user_property<double, struct first_double>          //*11 : double - (aka. double_first::type)
            | WithUnordered::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | WithUnordered::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type1 = Base{} | list_1;

        // types build with impl::DataAndPropertiesList and Create
        auto type2 =
            Base{}                                                               //
            | WithUnordered::Name                                                // 0  : Name / impl::Naming_
            | WithUnordered::user_property<bool, bool>                           // 1  : bool
            | WithUnordered::user_property<char, bool, bool>                     // 2  : char
            | WithUnordered::user_property<float>                                //*3  : float - (aka. just_float)
            | WithUnordered::user_property<float, float, int>                    // 4  : float
            | WithUnordered::Damage                                              // 5  : Damage / impl::Damaging_
            | WithUnordered::user_property<int>                                  // 6 : int
            | WithUnordered::user_property<int, struct first_int>                //*7  : int - (aka. int_first::type)
            | WithUnordered::user_property<std::string, struct first_string>     //*8  : string - (aka. string_first::type)
            | WithUnordered::user_property<std::string, struct second_string>    //*9  : string - (aka. string_second::type)
            | WithUnordered::user_property<double, struct second_double>         //*10 : double - (aka. double_second::type)
            | WithUnordered::user_property<double, struct first_double>          //*11 : double - (aka. double_first::type)
            | WithUnordered::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | WithUnordered::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            | Create;

        // types build with creator
        auto type3_creator =
            From::base<Base>                                                     //
            | WithUnordered::Name                                                // 0  : Name / impl::Naming_
            | WithUnordered::user_property<bool, bool>                           // 1  : bool
            | WithUnordered::user_property<char, bool, bool>                     // 2  : char
            | WithUnordered::user_property<float>                                //*3  : float - (aka. just_float)
            | WithUnordered::user_property<float, float, int>                    // 4  : float
            | WithUnordered::Damage                                              // 5  : Damage / impl::Damaging_
            | WithUnordered::user_property<int>                                  // 6  : int
            | WithUnordered::user_property<int, struct first_int>                //*7  : int - (aka. int_first::type)
            | WithUnordered::user_property<std::string, struct first_string>     //*8  : string - (aka. string_first::type)
            | WithUnordered::user_property<std::string, struct second_string>    //*9  : string - (aka. string_second::type)
            | WithUnordered::user_property<double, struct second_double>         //*10 : double - (aka. double_second::type)
            | WithUnordered::user_property<double, struct first_double>          //*11 : double - (aka. double_first::type)
            | WithUnordered::user_property<Damage, struct Damage_first>          // 12 : Damage added
            | WithUnordered::taged_property<Damaging_impl, struct Damage_first>  // ? -/13 : Damage duplication / impl::Damaging_ added (as different type than impl::UserProperty_<Damage,...>)
            | WithUnordered::taged_property<Damaging_impl>                       // !  : Damage / impl::Damaging_ - duplication
            ;
        auto type3 = type3_creator();

        static_assert(std::same_as<decltype(type1), decltype(type2)>);
        // static_assert(std::same_as<decltype(type1), decltype(type3)>);

        std::cout << "4 ********************************* " << '\n'
                  << '\n';

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
    return 0;
}
