#include "Usage/With.hpp"

#include <iostream>
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/GeneralFeatures.hpp"

struct Type {
    Name name;
    Damage dmg;
    Health hp;
};

int main() {
    static_assert(trait<Name>::accessable<Type>);
    static_assert(trait<Damage>::accessable<Type>);
    static_assert(trait<Health>::accessable<Type>);

    using general_type = impl::GeneralFeatures_<Type>;

    static_assert(trait<Name>::accessable<general_type>);
    static_assert(trait<Damage>::accessable<general_type>);
    static_assert(trait<Health>::accessable<general_type>);

    general_type type;

    static_assert(std::same_as<decltype(type.getType<Name>()), Name&>);
    static_assert(std::same_as<decltype(std::as_const(type).getType<Name>()), const Name&>);

    static_assert(std::same_as<decltype(type.getTypeTaged<Damage>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeTaged<Damage, int>()), void>);

    static_assert(std::same_as<decltype(type.getTypeOf(list<Damage>{})), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeOf(list<Damage, int>{})), void>);

    static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage>>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage, int>>()), void>);

    using general_type2 = add_properties_ordered<general_type,
                                                 AdvanceUserProperty<Health, struct x>::type,
                                                 AdvanceUserProperty<Protection>::type>;

    static_assert(std::same_as<decltype(type.getTaged<x>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type).getTaged<x>()), void>);

    general_type2 type2;

    type.getType<Name, 1>() = Name{"Name 2"};
    type.getType<Name, 0>() = Name{"Name 1"};

    type2.getType<Name, 1>() = Name{"Name 2"};
    type2.getType<Name, 0>() = Name{"Name 1"};

    std::cout << (std::string) type.getType<Name, 0>() << '\n';
    std::cout << (std::string) type.getType<Name, 1>() << '\n';

    std::cout << (std::string) type2.getType<Name, 0>() << '\n';
    std::cout << (std::string) type2.getType<Name, 1>() << '\n';

    static_assert(std::same_as<decltype(type2.getType<Name, 1>()), Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 1>()), const Name&>);

    static_assert(std::same_as<decltype(type2.getTaged<struct x>()), Health&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<struct x>()), const Health&>);
    static_assert(std::same_as<decltype(type2.getTaged()), Protection&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged()), const Protection&>);

    std::cout << name<general_type>() << '\n';
    std::cout << name<general_type2>() << '\n';

    std::cout << name<decltype(type2.getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(type2.getTaged())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged())>() << '\n';

    using general_type3 = add_properties_ordered<Type,
                                                 AdvanceUserProperty<Health, struct x>::type,
                                                 impl::GeneralFeatures_,
                                                 AdvanceUserProperty<Protection>::type>;
    // using general_type4 = add_properties_ordered<Type,
    //                                              impl::GeneralFeatures_,
    //                                              AdvanceUserProperty<Health, struct x>::type,
    //                                              AdvanceUserProperty<Protection>::type>;

    std::cout << name<general_type3>() << '\n';
    // std::cout << name<general_type4>() << '\n';
}