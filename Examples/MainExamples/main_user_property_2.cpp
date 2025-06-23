#include <iostream>
#include <typeinfo>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct MyType {
    // std::string name{};
};

using Type = Naming<MyType>;

template <typename T>
using BoolProperty = UserProperty<bool, T>;

template <typename T>
using IntProperty = UserProperty<int, T>;

// UserProperties are added after order_list properties if not on list itself:
using t1 = add_properties_ordered<
    BoolProperty<Type>,
    Damaging>;
using t2 = add_properties_ordered<
    Damaging<Type>,
    BoolProperty>;
using t3 = add_properties_ordered<
    Type,
    BoolProperty,
    Damaging>;
using t4 = add_properties_ordered<
    Type,
    Damaging,
    BoolProperty>;
//  will have same type and order of arguments in c-tor

using t5 = add_properties_ordered<
    Type,
    IntProperty,
    Damaging,
    BoolProperty>;

static_assert(std::is_same_v<t1, t2>);
static_assert(std::is_same_v<t2, t3>);
static_assert(std::is_same_v<t3, t4>);

int main() {
    std::cout << name<t1>() << '\n';
    std::cout << name<t2>() << '\n';
    std::cout << name<t3>() << '\n';
    std::cout << name<t4>() << '\n';
    std::cout << name<t5>() << '\n';

    t5 type{Name{"Rat"}, Damage{5}, 24, true};

    decltype(auto) s = trait<Name>::get(type);
    decltype(auto) d = trait<Damage>::get(type);
#ifdef NO_PREMADE_PROPERTIES
    [[maybe_unused]] decltype(auto) s2 = type.getType<Name>();
    [[maybe_unused]] decltype(auto) d2 = type.getType<Damage>();
#else
    [[maybe_unused]] decltype(auto) s2 = type.getName();
    [[maybe_unused]] decltype(auto) d2 = type.getDamage();
#endif
    decltype(auto) i = type.getType<int>();
    decltype(auto) i2 = std::as_const(type).getType<int>();
    decltype(auto) b = type.getType<bool>();
    decltype(auto) b2 = std::as_const(type).getType<bool>();

    std::cout << std::string{s} << '\n';
    std::cout << d.type() << '\n';
    std::cout << d.value() << '\n';
    std::cout << i << '\n';
    i += 5;
    std::cout << i2 << '\n';
    std::cout << b << '\n';
    b = false;
    std::cout << b2 << '\n';

    return 0;
}
