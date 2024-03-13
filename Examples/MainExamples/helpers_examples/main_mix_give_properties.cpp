#include <iostream>
#include "../../../Object/Properties/Properties.hpp"
#include "../../demangle_type_name.hpp"

struct Type {
    Name name;
};

using Type0 = Living<Type>;
using Type1 = add_properties<Type, Living, Healing, Damaging>;
using Type2 = add_properties<Type0, Living, Healing, Damaging>;
using Type3 = Healing<Type2>;
using Type4 = add_properties<Type3, Living, Healing>;

static_assert(std::is_same_v<Type1, Type2>);
static_assert(std::is_same_v<Type2, Type3>);
static_assert(std::is_same_v<Type3, Type4>);

using helpers::append_and_order_property_lists;
using helpers::create_ordered_property_list;
using helpers::is_type_with_added_properties;
using helpers::Scheme;

int main() {
    auto print = [](auto t) {
        using T = decltype(t);
        std::cout << is_type_with_added_properties<typename T::property_data::base_type> << '\n';
        std::cout << "RESULT type   = " << name<T>() << '\n';
        std::cout << "Base type     = " << name<typename T::property_data::base_type>() << '\n';
        std::cout << "Property type = " << name<typename T::property_data::property_type>() << "\n\n";
    };

    print(Type0{});
    print(Type1{});
    print(Type2{});
    print(Type3{});
    print(Type4{});

    std::cout << "create_ordered_property_list           = " << name<create_ordered_property_list<Living, Healing>>() << '\n';
    std::cout << "Scheme<Type0>::list                    = " << name<Scheme<Type0>::list>() << '\n';
    std::cout << "append_and_order_property_lists<Type0> = "
              << name<append_and_order_property_lists<  //
                     Scheme<Type0>::list,               //
                     create_ordered_property_list<Living, Healing>>>()
              << '\n';
    std::cout << "Property<Living>  priority = " << Property<Living>::value << '\n';
    std::cout << "Property<Living_> priority = " << Property<impl::Living_>::value << '\n';

    return 0;
}
