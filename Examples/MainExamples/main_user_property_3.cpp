#include <iostream>
#include <typeinfo>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct MyType {
    MyType() noexcept = default;
    MyType(auto&&...) noexcept {};  // sink extra arguments
};

using Type_basic = UserProperty<Damage, MyType>;
static_assert(getType_template_able<Type_basic, Damage>);

using Type_no_nest = UserProperty<Damage, UserProperty<Damage, UserProperty<Damage, MyType>>>;                              // UserProperty don't allow nesting - trait_accessable concept check disallow it
using Type_unlimited_nest = impl::UserProperty_<Damage, impl::UserProperty_<Damage, impl::UserProperty_<Damage, MyType>>>;  // impl::UserProperty_ allow unlimited nesting
using Type_unlimited_nest_collapse = add_properties_ordered<Type_unlimited_nest>;

static_assert(std::is_same_v<
              UserPropertyAdapter<Damage>::once<Type_no_nest>,
              UserProperty<Damage, Type_no_nest>>);

using Type_nest_one = add_properties_ordered<Type_no_nest, UserPropertyAdapter<Damage>::once, UserPropertyAdapter<Damage>::once>;   // add_properties allow nest one level at the time
using Type_nest_two = add_properties_ordered<Type_nest_one, UserPropertyAdapter<Damage>::once, UserPropertyAdapter<Damage>::once>;  // add_properties allow nest one level at the time

template <typename T, typename TYPE = Damage, typename C = struct TOKEN>
using UserProperty2 = UserProperty<TYPE, T, C, struct TEST, void>;
using Type_complex = add_properties_ordered<MyType, UserProperty2>;          // add_properties allow nest one level at the time
using Type_complex_2 = add_properties_ordered<Type_complex, UserProperty2>;  // add_properties allow nest one level at the time

template <typename T>
using UserProperty3 = UserProperty<Damage, T, struct TAG>;
using Type_tag_complex = add_properties_ordered<Type_complex, UserProperty3>;

template <typename TYPE>
using Type_adapter = add_properties_ordered<Type_basic, UserPropertyAdapter<TYPE>::template once>;

int main() {
    std::cout << "taged_list                     = " << name<taged_list<UserProperty2>>() << '\n';
    std::cout << "Property                       = " << name<Property<UserProperty2>::apply<tag>>() << '\n';
    std::cout << '\n';

    std::cout << "Type_basic                     = " << name<Type_basic>() << '\n';
    std::cout << "Type_no_nest                   = " << name<Type_no_nest>() << '\n';
    std::cout << "Type_unlimited_nest            = " << name<Type_unlimited_nest>() << '\n';
    std::cout << "Type_unlimited_nest_collapse   = " << name<Type_unlimited_nest_collapse>() << '\n';
    std::cout << "Type_nest_one                  = " << name<Type_nest_one>() << '\n';
    std::cout << "Type_nest_two                  = " << name<Type_nest_two>() << '\n';
    std::cout << "Type_complex                   = " << name<Type_complex>() << '\n';
    std::cout << "Type_complex_2                 = " << name<Type_complex_2>() << '\n';
    std::cout << "Type_tag_complex               = " << name<Type_tag_complex>() << '\n';
    std::cout << "Type_adapter<Damage>           = " << name<Type_adapter<Damage>>() << '\n';

    using Type_nest_unlimited_one = add_properties_ordered<Type_unlimited_nest, UserPropertyAdapter<Damage>::once>;
    using Type_nest_unlimited_two = add_properties_ordered<Type_nest_unlimited_one, UserPropertyAdapter<Damage>::once>;

    std::cout << "Type_nest_unlimited_one        = " << name<Type_nest_unlimited_one>() << '\n';
    std::cout << "Type_nest_unlimited_two        = " << name<Type_nest_unlimited_two>() << '\n';

    Type_no_nest type_no{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_no_nest" << '\n';
    std::cout << ((type_no.getType<Damage>() == trait<Damage>::get(type_no)))
              << '\n';
    std::cout << type_no.getType<Damage>() << '\n';
    std::cout << '\n';

    Type_unlimited_nest type_u{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_unlimited_nest" << '\n';
    std::cout << ((type_u.getType<Damage>() == trait<Damage>::get(type_u)))
              << '\n';
    std::cout << type_u.getType<Damage>() << '\n';
    std::cout << type_u.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type_u.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    static_assert(&type_u.getType<Damage, 1>() == &type_u.getType<1>());
    static_assert(&type_u.getType<Damage, 2>() == &type_u.getType<2>());
    std::cout << '\n';

    Type_nest_unlimited_one type2{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_nest_unlimited_one" << '\n';
    std::cout << ((type2.getType<Damage>() == trait<Damage>::get(type2)))
              << '\n';
    std::cout << type2.getType<Damage>() << '\n';
    std::cout << '\n';

    Type_nest_unlimited_two type3{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_nest_unlimited_two" << '\n';
    std::cout << ((type3.getType<Damage>() == trait<Damage>::get(type3)))
              << '\n';
    std::cout << type3.getType<Damage>() << '\n';
    std::cout << '\n';

    Type_complex type4{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_complex" << '\n';
    std::cout << ((type4.getType<Damage>() == trait<Damage>::get(type4)))
              << '\n';
    std::cout << type4.getType<Damage>() << '\n';
    std::cout << '\n';

    Type_complex_2 type5{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_complex_2" << '\n';
    std::cout << ((type5.getType<Damage>() == trait<Damage>::get(type5)))
              << '\n';
    std::cout << type5.getType<Damage>() << '\n';
    std::cout << '\n';

    Type_tag_complex type6{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_tag_complex" << '\n';
    std::cout << ((type6.getType<Damage>() == trait<Damage>::get(type6)))
              << '\n';
    std::cout << type6.getType<Damage>() << '\n';
    std::cout << type6.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    static_assert(&type6.getType<Damage, 1>() == &type6.getType<1>());
    std::cout << '\n';

    using unlimited_nest_1 = impl::UserProperty_<Name, impl::UserProperty_<Name, MyType, int>, int>;
    using unlimited_nest_2 = impl::UserProperty_<Damage, impl::UserProperty_<Damage, MyType, int>, int>;

    std::cout << "unlimited_nest_1            = " << name<unlimited_nest_1>() << '\n';
    std::cout << "unlimited_nest_2            = " << name<unlimited_nest_2>() << '\n';
    std::cout << "unlimited_nest_1 collapse   = " << name<add_properties_ordered<unlimited_nest_1>>() << '\n';
    std::cout << "unlimited_nest_2 collapse   = " << name<add_properties_ordered<unlimited_nest_2>>() << '\n';
    std::cout << '\n';
    static_assert(std::same_as<add_properties_ordered<unlimited_nest_1>, impl::UserProperty_<Name, MyType, int>>);
    static_assert(std::same_as<add_properties_ordered<unlimited_nest_2>, impl::UserProperty_<Damage, MyType, int>>);

#ifndef NO_PREMADE_PROPERTIES
    using unlimited_nest_3 = impl::Naming_<impl::Naming_<MyType>>;
    using unlimited_nest_4 = impl::Damaging_<impl::Damaging_<MyType, int>, int>;
    std::cout << "unlimited_nest_3            = " << name<unlimited_nest_3>() << '\n';
    std::cout << "unlimited_nest_4            = " << name<unlimited_nest_4>() << '\n';
    std::cout << "unlimited_nest_3 collapse   = " << name<add_properties_ordered<unlimited_nest_3>>() << '\n';
    std::cout << "unlimited_nest_4 collapse   = " << name<add_properties_ordered<unlimited_nest_4>>() << '\n';
    static_assert(std::same_as<add_properties_ordered<unlimited_nest_3>, impl::Naming_<MyType>>);
    static_assert(std::same_as<add_properties_ordered<unlimited_nest_4>, impl::Damaging_<MyType, int>>);
#endif

    return 0;
}
