#include <iostream>
#include <typeinfo>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct MyType {
    MyType() noexcept = default;
    MyType(auto&&...) noexcept {};  // sink extra arguments
};

using Type_basic = UserProperty<Damage, MyType>;
static_assert(traits::GetTypeTemplateAccessable<Type_basic, Damage>);

using Type_no_nest = UserProperty<Damage, UserProperty<Damage, UserProperty<Damage, MyType>>>;                              // UserProperty don't allow nesting - trait_accessable concept check disallow it
using Type_unlimited_nest = impl::UserProperty_<Damage, impl::UserProperty_<Damage, impl::UserProperty_<Damage, MyType>>>;  // impl::UserProperty_ allow unlimited nesting
using Type_unlimited_nest_collapse = add_properties<Type_unlimited_nest>;

static_assert(std::is_same_v<
              UserPropertyAdapter<Damage>::type<Type_no_nest>,
              UserProperty<Damage, Type_no_nest>>);

using Type_nest_one = add_properties<Type_no_nest, UserPropertyAdapter<Damage>::type, UserPropertyAdapter<Damage>::type>;   // add_properties allow nest one level at the time
using Type_nest_two = add_properties<Type_nest_one, UserPropertyAdapter<Damage>::type, UserPropertyAdapter<Damage>::type>;  // add_properties allow nest one level at the time

template <typename T, typename TYPE = Damage, typename C = struct TOKEN>
using UserProperty2 = UserProperty<TYPE, T, C, struct TEST, void>;
using Type_complex = add_properties<MyType, UserProperty2>;  // add_properties allow nest one level at the time
using Type_complex_2 = add_properties<Type_complex, UserProperty2>;  // add_properties allow nest one level at the time

template <typename T>
using UserProperty3 = UserProperty<Damage, T, struct TAG>;
using Type_tag_complex = add_properties<Type_complex, UserProperty3>;

template <typename TYPE>
using Type_adapter = add_properties<Type_basic, UserPropertyAdapter<TYPE>::template type>;

int main() {
    std::cout << "taged_list                     = " << name<taged_list<UserProperty2>>() << '\n';
    std::cout << "Property                       = " << name<Property<UserProperty2>::type<tag>>() << '\n';
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

    using Type_nest_unlimited_one = add_properties<Type_unlimited_nest, UserPropertyAdapter<Damage>::type>;
    using Type_nest_unlimited_two = add_properties<Type_nest_unlimited_one, UserPropertyAdapter<Damage>::type>;

    std::cout << "Type_nest_unlimited_one        = " << name<Type_nest_unlimited_one>() << '\n';
    std::cout << "Type_nest_unlimited_two        = " << name<Type_nest_unlimited_two>() << '\n';

    Type_no_nest type_no{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_no_nest" << '\n';
    std::cout << ((type_no.getType<Damage>() == Damagingable_trait::get(type_no)) and  //
                  (type_no.getType<Damage>() == traits::accessType<Damage>::get(type_no)))
              << '\n';
    std::cout << type_no.getType<Damage>() << '\n';
    std::cout << type_no.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type_no.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type_no.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type_no.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_unlimited_nest type_u{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_unlimited_nest" << '\n';
    std::cout << ((type_u.getType<Damage>() == Damagingable_trait::get(type_u)) and  //
                  (type_u.getType<Damage>() == traits::accessType<Damage>::get(type_u)))
              << '\n';
    std::cout << type_u.getType<Damage>() << '\n';
    std::cout << type_u.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type_u.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type_u.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type_u.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_nest_unlimited_one type2{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_nest_unlimited_one" << '\n';
    std::cout << ((type2.getType<Damage>() == Damagingable_trait::get(type2)) and  //
                  (type2.getType<Damage>() == traits::accessType<Damage>::get(type2)))
              << '\n';
    std::cout << type2.getType<Damage>() << '\n';
    std::cout << type2.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type2.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type2.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type2.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_nest_unlimited_two type3{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_nest_unlimited_two" << '\n';
    std::cout << ((type3.getType<Damage>() == Damagingable_trait::get(type3)) and  //
                  (type3.getType<Damage>() == traits::accessType<Damage>::get(type3)))
              << '\n';
    std::cout << type3.getType<Damage>() << '\n';
    std::cout << type3.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type3.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type3.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type3.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_complex type4{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_complex" << '\n';
    std::cout << ((type4.getType<Damage>() == Damagingable_trait::get(type4)) and  //
                  (type4.getType<Damage>() == traits::accessType<Damage>::get(type4)))
              << '\n';
    std::cout << type4.getType<Damage>() << '\n';
    std::cout << type4.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type4.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type4.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type4.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_complex_2 type5{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_complex_2" << '\n';
    std::cout << ((type5.getType<Damage>() == Damagingable_trait::get(type5)) and  //
                  (type5.getType<Damage>() == traits::accessType<Damage>::get(type5)))
              << '\n';
    std::cout << type5.getType<Damage>() << '\n';
    std::cout << type5.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type5.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type5.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type5.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    Type_tag_complex type6{Damage{5}, Damage{10}, Damage{15}, Damage{20}, Damage{25}};
    std::cout << "Type_tag_complex" << '\n';
    std::cout << ((type6.getType<Damage>() == Damagingable_trait::get(type6)) and  //
                  (type6.getType<Damage>() == traits::accessType<Damage>::get(type6)))
              << '\n';
    std::cout << type6.getType<Damage>() << '\n';
    std::cout << type6.getType<Damage, 1>() << '\n';  // dig to deeper type if can
    std::cout << type6.getType<Damage, 2>() << '\n';  // dig to even deeper type if can
    std::cout << type6.getType<Damage, 3>() << '\n';  // dig to even deeper type if can
    std::cout << type6.getType<Damage, 4>() << '\n';  // dig to even deeper type if can
    std::cout << '\n';

    return 0;
}
