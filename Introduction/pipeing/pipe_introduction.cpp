#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"

#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Introduction/pipeing/order_list.hpp"

#include "Usage/With.hpp"

struct Base {
    int x{};
    int y{};
};

int main() {
    // 1.a
    {
        auto create_type =
            From::base<Base>              //
            | With::user_property<int>    //
            | With::property<Protecting>  //
            | With::Damage                //
            ;
        auto type = create_type(
            Damage{5, DamageType::Physical},     // earlier on order_list
            Protection{10, BodyLocation::Legs},  // later on order_list
            15                                   // not on order_list
        );

        std::cout << "Example 1.a\n";
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "int        = " << trait<int>::get(type) << '\n';
        std::cout << '\n';
    }
    // 1.b
    {
        auto create_type =
            From::base<Base>                       //
            | WithUnordered::user_property<int>    // first: int
            | WithUnordered::property<Protecting>  // later: Protection
            | WithUnordered::Damage                // last: Damage
            ;
        auto type = create_type(
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical});

        std::cout << "Example 1.b\n";
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "int        = " << trait<int>::get(type) << '\n';
        std::cout << '\n';
    }
    // 2
    {
        auto property_Name = With::Name;
        list list_Name = With::Name;  // implicit conversion from Property<Naming> to list<Naming<tag>>
        auto tlist = With::Name | With::Health | With::Protection | With::Damage;
        auto nlist = tlist | With::user_property<int>;

        std::cout << "Example 2\n";
        std::cout << "property_Name  = " << name<decltype(property_Name)>() << '\n';
        std::cout << "list_Name      = " << name<decltype(list_Name)>() << '\n';
        std::cout << "tlist          = " << name<decltype(tlist)>() << '\n';
        std::cout << "nlist          = " << name<decltype(nlist)>() << '\n';
        std::cout << '\n';
    }

    constexpr auto default_x = 17;
    constexpr auto default_y = 89;
    // 3.a
    {
        Base base_type{default_x, default_y};
        auto tlist = With::Name | With::Health | With::Protection | With::Damage;  // order as given
        auto new_type = base_type | tlist;
        auto new_type2 = base_type | (With::Name | With::Health | With::Protection | With::Damage);
        auto new_type3 = Base{default_x, default_y} | tlist;

        std::cout << "Example 3.a\n";
        std::cout << "tlist       = " << name<decltype(tlist)>() << '\n';
        std::cout << "new_type    = " << name<decltype(new_type)>() << '\n';
        std::cout << "new_type2   = " << name<decltype(new_type2)>() << '\n';
        std::cout << "new_type3   = " << name<decltype(new_type3)>() << '\n';
        std::cout << "new_type.x  = " << new_type.x << '\n';
        std::cout << "new_type.y  = " << new_type.y << '\n';
        std::cout << "new_type2.x = " << new_type2.x << '\n';
        std::cout << "new_type2.y = " << new_type2.y << '\n';
        std::cout << "new_type3.x = " << new_type3.x << '\n';
        std::cout << "new_type3.y = " << new_type3.y << '\n';
        std::cout << '\n';
    }
    // 3.b
    {
        Base base_type{default_x, default_y};
        auto new_type =
            base_type           // order from order_list
            | With::Name        //
            | With::Health      //
            | With::Protection  //
            | Create            //
            ;
        trait<Name>::get(new_type) = Name{"new_type"};

        std::cout << "Example 3.b\n";
        std::cout << "new_type   = " << name<decltype(new_type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(new_type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(new_type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(new_type) << '\n';
        std::cout << "x          = " << new_type.x << '\n';
        std::cout << "y          = " << new_type.y << '\n';
        std::cout << '\n';
    }
}
