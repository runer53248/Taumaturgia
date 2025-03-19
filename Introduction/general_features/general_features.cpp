#include <iostream>
#include "Examples/demangle_type_name.hpp"
#include "Usage/With.hpp"

#include "Introduction/parse_type_name.hpp"
#include "Taumaturgia/Properties/GeneralFeatures.hpp"

struct Base {
    Name name{"Name c"};  // default in base
    Damage dmg;
    Health hp;
};

struct name_t {};

template <>
struct UserDefaultValue<Name> {  // default in ordered property
    static constexpr auto value = [] { return Name{"Name a"}; };
};
template <>
struct UserDefaultValue<Name, name_t> {  // default in unordered property
    static constexpr auto value = [] { return Name{"Name b"}; };
};

int main() {
    prepare_buildin_defaults<Name>();  // sets default for buildin properties

    static_assert(trait<Name>::accessable<Base>);
    static_assert(trait<Damage>::accessable<Base>);
    static_assert(trait<Health>::accessable<Base>);

    using general_type = GeneralFeatures<Base>;

    static_assert(trait<Name>::accessable<general_type>);
    static_assert(trait<Damage>::accessable<general_type>);
    static_assert(trait<Health>::accessable<general_type>);

    general_type type;

    static_assert(std::same_as<decltype(type.getTaged<0>()), Name&>);
    static_assert(std::same_as<decltype(type.getTaged<1>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTaged<2>()), Health&>);
    static_assert(std::same_as<decltype(type.getTaged<3>()), void>);

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
                                                 AdvanceUserProperty<Name, name_t>::type,
                                                 //  AdvanceUserProperty<Name>::type, // order depends Naming_impl
                                                 //  AdvanceUserProperty<Protection>::type // order depends of Protecting_impl
                                                 Naming_impl,
                                                 Protecting_impl>;

    static_assert(std::same_as<decltype(type.getTaged<x>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type).getTaged<x>()), void>);
    static_assert(std::same_as<decltype(type.getTaged()), Name&>);
    static_assert(std::same_as<decltype(std::as_const(type).getTaged()), const Name&>);

    general_type2 type2;

    std::cout << "type2 0 = " << (std::string)type2.getType<Name, 0>() << '\n';
    std::cout << "type2 1 = " << (std::string)type2.getType<Name, 1>() << '\n';
    std::cout << "type2 2 = " << (std::string)type2.getType<Name, 2>() << '\n'
              << '\n';

    type2.getType<Name, 0>() = Name{"Name 1"};
    type2.getType<Name, 1>() = Name{"Name 2"};
    type2.getType<Name, 2>() = Name{"Name 3"};
    type2.getType<Protection, 0>() = Protection{10};
    type2.getType<Health, 0>() = Health{100};
    type2.getType<Health, 1>() = Health{200};

    std::cout << "type2 0 = " << (std::string)type2.getType<Name, 0>() << '\n';
    std::cout << "type2 1 = " << (std::string)type2.getType<Name, 1>() << '\n';
    std::cout << "type2 2 = " << (std::string)type2.getType<Name, 2>() << '\n'
              << '\n';

    std::cout << "taged 1 = " << (std::string)type2.getTaged<1>() << '\n';
    std::cout << "taged 2 = " << (std::string)type2.getTaged<2>() << '\n'
              << '\n';

    std::cout << "TypeTaged p = " << type2.getTypeTaged<Protection>().armorClass() << '\n';
    std::cout << "TypeTaged h1 = " << type2.getTypeTaged<Health, x>().value() << '\n';
    std::cout << "TypeTaged h2 = " << type2.getTypeTaged<Health>().value() << '\n';
    std::cout << "TypeTaged 1 = " << (std::string)type2.getTypeTaged<Name>() << '\n';
    std::cout << "TypeTaged 2 = " << (std::string)type2.getTypeTaged<Name, name_t>() << '\n';

    {
        using featured_general_type2 = GeneralFeatures<general_type2>;

        featured_general_type2 feature_type2;
        feature_type2.getType<Protection, 0>() = Protection{10};

        std::cout << parse_type_name<featured_general_type2>() << '\n';
        feature_type2.getType<Protection, 0>() = Protection{10};
    }

    static_assert(std::same_as<decltype(type2.getType<Name, 1>()), Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 1>()), const Name&>);

    static_assert(std::same_as<decltype(type2.getTaged<struct x>()), Health&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<struct x>()), const Health&>);

    static_assert(std::same_as<decltype(type2.getTaged()), Protection&>);
    static_assert(std::same_as<decltype(type2.getTaged<1>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTaged<2>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTaged<3>()), Damage&>);
    static_assert(std::same_as<decltype(type2.getTaged<4>()), Health&>);
    static_assert(std::same_as<decltype(type2.getTaged<5>()), void>);

    static_assert(std::same_as<decltype(std::as_const(type2).getTaged()), const Protection&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<1>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<2>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<3>()), const Damage&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<4>()), const Health&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<5>()), void>);

    std::cout << parse_type_name<general_type>() << '\n';
    std::cout << parse_type_name<general_type2>() << '\n';

    std::cout << name<decltype(type2.getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(type2.getTaged())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged())>() << '\n';

    static_assert(not is_property<GeneralFeatures>);
}