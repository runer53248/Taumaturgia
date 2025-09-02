#include <iostream>
#include "Examples/Checks.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/Properties.hpp"

struct Type {
    Name name;
};

using Type0 = Living<Type>;
using Type1 = add_properties_ordered<Type, Living, Healing, Damaging>;
using Type2 = add_properties_ordered<Type0, Living, Healing, Damaging>;
using Type3 = Healing<Type2>;
using Type4 = add_properties_ordered<Type3, Living, Healing>;

static_assert(std::is_same_v<Type1, Type2>);
static_assert(std::is_same_v<Type2, Type3>);
static_assert(std::is_same_v<Type3, Type4>);

using helpers::append_and_order_property_lists;
using helpers::create_ordered_property_list;
using helpers::Scheme_ordered;

int main() {
    auto print = [](auto t) {
        using T = decltype(t);
        std::cout << have_property_data<typename T::property_data::base_type> << '\n';
        std::cout << "RESULT type   = " << name<T>() << '\n';
        std::cout << "Base type     = " << name<typename T::property_data::base_type>() << '\n';
        std::cout << "Property type = " << name<typename T::property_data::ordered_property_type>() << "\n\n";
    };

    print(Type0{});
    print(Type1{});
    print(Type2{});
    print(Type3{});
    print(Type4{});

    std::cout << "create_ordered_property_list           = " << name<create_ordered_property_list<Living, Healing>>() << '\n';
    std::cout << "Scheme_ordered<Type0>::list_t          = " << name<Scheme_ordered<Type0>::list_t>() << '\n';
    std::cout << "append_and_order_property_lists<Type0> = "
              << name<append_and_order_property_lists<  //
                     Scheme_ordered<Type0>::list_t,             //
                     create_ordered_property_list<Living, Healing>>>()
              << '\n';
    std::cout << "Property_ordered<Living>  priority = " << Property_ordered<Living>::value << '\n';
    std::cout << "Property_ordered<Living_> priority = " << Property_ordered<Living_impl>::value << '\n';

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
