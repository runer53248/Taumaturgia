#define IGNORE_ORDER_LIST

#include "Examples/Checks.hpp"
#include "Usage/With.hpp"
#include "default_values.hpp"
#include "print.hpp"

struct Base {
    int x;
    int y;
};

int main() {
    // MARK: extra example
    list with_list_Name = With::Name;  // implicit conversion from Property<Naming> to list<Naming<tag>>
    auto with_auto_Name = With::Name;  // ! auto deduce Property<Naming> (single object is not a list)

    static_assert(std::same_as<
                  decltype(with_list_Name | With::Health),    // append to list
                  decltype(with_auto_Name | With::Health)>);  // create list from properties

    auto base_with_list_Name = Base{default_x, default_y} | with_list_Name;  // object
    // auto base_with_auto_Name = Base{default_x, default_y} | with_auto_Name;  // ! creator may be misinterpret
    auto base_with_auto_Name = From::base<Base> | with_auto_Name;  // ? creator now have distinctive pipe

    std::cout << '\n';
    std::cout << "base_with_list_Name =    " << name<decltype(base_with_list_Name)>() << '\n';  // object
    std::cout << "base_with_auto_Name =    " << name<decltype(base_with_auto_Name)>() << '\n';  // ! creator
    std::cout << '\n';
#ifndef NO_PREMADE_PROPERTIES
    base_with_list_Name.getName() = default_name;  // used as object
#else
    base_with_list_Name.getType<Name>() = default_name;  // used as object
#endif
    auto type = base_with_list_Name;
    std::cout << "creator type:\n";

#ifndef NO_PREMADE_PROPERTIES
    std::cout << "name = " << type.getName().operator std::string() << '\n';
#else
    base_with_list_Name.getType<Name>() = default_name;  // used as object
#endif
    std::cout << "x    = " << type.x << '\n';
    std::cout << "y    = " << type.y << '\n';

    auto type2 = base_with_auto_Name(default_name, default_x, default_y);  // used as creator
    std::cout << "creator type:\n";
#ifndef NO_PREMADE_PROPERTIES
    std::cout << "name = " << type2.getName().operator std::string() << '\n';
#else
    base_with_list_Name.getType<Name>() = default_name;  // used as object
#endif
    std::cout << "x    = " << type2.x << '\n';
    std::cout << "y    = " << type2.y << '\n';

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
