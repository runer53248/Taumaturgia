#include <boost/core/demangle.hpp>
#include <iostream>
#include <typeinfo>
// #include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/Properties/UserProperty.hpp"
#include "Examples/preety_print.hpp"

template <class T>
std::string name() {
    return boost::core::demangle(typeid(T).name());
}

// UserProperties are added after order_list properties if not on list itself:
//       add_properties<UserProperty<type>, Damagingable>
//       add_properties<Damagingable<type>, UserProperty>
//       add_properties<type, UserProperty, Damagingable>
//       add_properties<type, Damagingable, UserProperty>
//  will have same type and order of arguments in c-tor

struct Type {
    std::string name{};
};

template <typename TYPE>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<T, TYPE>;
};

template <typename T>
using BoolProperty = UserProperty<T, bool>;

using t1 = add_properties<BoolProperty<Type>, Damaging>;
using t2 = add_properties<Damaging<Type>, BoolProperty>;
using t3 = add_properties<Type, BoolProperty, Damaging>;
using t4 = add_properties<Type, Damaging, BoolProperty>;

static_assert(std::is_same_v<t1, t2>);
static_assert(std::is_same_v<t2, t3>);
static_assert(std::is_same_v<t3, t4>);

int main() {
    std::cout << name<t1>() << '\n';
    std::cout << name<t2>() << '\n';
    std::cout << name<t3>() << '\n';
    std::cout << name<t4>() << '\n';

    t1 type{Name{"Rat"}, Damage{5}, true};

    std::string s = type.name;
    Damage d = type.getDamage();
    bool b = type.getType();

    std::cout << s << '\n';
    std::cout << d.type() << '\n';
    std::cout << d.value() << '\n';
    std::cout << b << '\n';

    return 0;
}
