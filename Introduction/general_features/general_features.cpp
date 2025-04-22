#include <iostream>
#include <print>
#include "Introduction/parse_type_name.hpp"
#include "Taumaturgia/Properties/GeneralFeatures.hpp"

#include "Examples/PreetyPrint/preety_print.hpp"

struct Type {
    Name name{"Name c"};  // default in base
    Damage dmg;
    Health hp;
    int type{500};
};

struct name_t {};
struct int_t {};

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

    static_assert(trait_accessable<Type, Name>);
    static_assert(trait_accessable<Type, Damage>);
    static_assert(trait_accessable<Type, Health>);
    static_assert(trait_accessable<Type, int>);

    using general_type = GeneralFeatures<Type>;
    using general_type2 = add_properties_ordered<general_type,
                                                 AdvanceUserProperty<Health, struct x>::type,
                                                 AdvanceUserProperty<Name, name_t>::type,
                                                 AdvanceUserProperty<int, int_t>::type,
                                                 Naming_impl,
                                                 Protecting_impl>;

    static_assert(trait_accessable<general_type, Name>);
    static_assert(trait_accessable<general_type, Damage>);
    static_assert(trait_accessable<general_type, Health>);

    static_assert(trait_accessable<general_type2, Name>);
    static_assert(trait_accessable<general_type2, Damage>);
    static_assert(trait_accessable<general_type2, Health>);
    static_assert(trait_accessable<general_type2, Protection>);
    static_assert(not trait_accessable<general_type2, CureHealth>);

    general_type type;
    general_type2 type2;

    // GeneralFeatures_<>::getTaged
    static_assert(std::same_as<decltype(type.getTaged()), Name&>);
    static_assert(std::same_as<decltype(type.getTaged<1>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTaged<2>()), Health&>);
    static_assert(std::same_as<decltype(type.getTaged<3>()), void>);
    static_assert(std::same_as<decltype(type.getTaged<x>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type).getTaged<x>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type).getTaged()), const Name&>);
    // Features_<>::getTaged
    static_assert(std::same_as<decltype(type2.getTaged<x>()), Health&>);
    static_assert(std::same_as<decltype(type2.getTaged<name_t>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTaged()), Protection&>);
    static_assert(std::same_as<decltype(type2.getTaged<1>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTaged<2>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTaged<3>()), Damage&>);
    static_assert(std::same_as<decltype(type2.getTaged<4>()), Health&>);
    static_assert(std::same_as<decltype(type2.getTaged<5>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<x>()), const Health&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<name_t>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged()), const Protection&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<1>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<2>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<3>()), const Damage&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<4>()), const Health&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getTaged<5>()), void>);

    // GeneralFeatures_<>::getType
    static_assert(std::same_as<decltype(type.getType<Name>()), Name&>);
    static_assert(std::same_as<decltype(type.getType<Name, 1>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type).getType<Name>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type).getType<Name, 1>()), void>);
    // Features_<>::getType
    static_assert(std::same_as<decltype(type2.getType<Name, 0>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<Name, 1>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<Name, 2>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<Name, 3>()), void>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 0>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 1>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 2>()), const Name&>);
    static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 3>()), void>);
    // Features_<>::getType new kind
    static_assert(std::same_as<decltype(type2.getType<0>()), Protection&>);
    static_assert(std::same_as<decltype(type2.getType<1>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<2>()), Health&>);
    static_assert(std::same_as<decltype(type2.getType<3>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<4>()), int&>);
    static_assert(std::same_as<decltype(type2.getType<5>()), Name&>);
    static_assert(std::same_as<decltype(type2.getType<6>()), Damage&>);
    static_assert(std::same_as<decltype(type2.getType<7>()), Health&>);
    static_assert(std::same_as<decltype(type2.getType<8>()), int&>);
    static_assert(std::same_as<decltype(type2.getType<9>()), void>);

    static_assert(&type2.getType<0>() == &type2.getTypeTaged<Protection>());
    static_assert(&type2.getType<1>() == &type2.getTypeTaged<Name>());
    static_assert(&type2.getType<1>() == &type2.getType<Name, 0>());
    static_assert(&type2.getType<2>() == &type2.getTypeTaged<Health, x>());
    static_assert(&type2.getType<2>() == &type2.getType<Health, 0>());
    static_assert(&type2.getType<3>() == &type2.getTypeTaged<Name, name_t>());
    static_assert(&type2.getType<3>() == &type2.getType<Name, 1>());
    static_assert(&type2.getType<4>() == &type2.getType<int, 0>());
    static_assert(&type2.getType<5>() == &type2.getType<Name, 2>());
    static_assert(&type2.getType<6>() == &type2.getType<Damage>());
    static_assert(&type2.getType<7>() == &type2.getType<Health, 1>());

    // GeneralFeatures_<>::getTypeTaged
    static_assert(std::same_as<decltype(type.getTypeTaged<Damage>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeTaged<Damage, int>()), void>);
    // Features_<>::getTypeTaged
    static_assert(std::same_as<decltype(type2.getTypeTaged<Damage>()), Damage&>);
    static_assert(std::same_as<decltype(type2.getTypeTaged<Health, x>()), Health&>);
    static_assert(std::same_as<decltype(type2.getTypeTaged<Name, name_t>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTypeTaged<Damage, int>()), void>);

    static_assert(&type2.getType<Health, 0>() == &type2.getTypeTaged<Health, x>());
    static_assert(&type2.getType<Health, 1>() == &type2.getTypeTaged<Health>());
    static_assert(&type2.getType<Name, 0>() == &type2.getTypeTaged<Name>());
    static_assert(&type2.getType<Name, 1>() == &type2.getTypeTaged<Name, name_t>());

    // GeneralFeatures_<>::getTypeOf
    static_assert(std::same_as<decltype(type.getTypeOf(list<Damage>{})), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeOf(list<Damage, int>{})), void>);
    // Features_<>::getTypeOf
    static_assert(std::same_as<decltype(type2.getTypeOf(list<Damage>{})), Damage&>);
    static_assert(std::same_as<decltype(type2.getTypeOf(list<Name, name_t>{})), Name&>);
    static_assert(std::same_as<decltype(type2.getTypeOf(list<Damage, int>{})), void>);

    // GeneralFeatures_<>::getTypeOfSignature
    static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage>>()), Damage&>);
    static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage, int>>()), void>);
    // Features_<>::getTypeOfSignature
    static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Damage>>()), Damage&>);
    static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Name, name_t>>()), Name&>);
    static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Damage, int>>()), void>);

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

    std::cout << "TypeTaged p  = " << type2.getTypeTaged<Protection>().armorClass() << '\n';
    std::cout << "TypeTaged h1 = " << type2.getTypeTaged<Health, x>().value() << '\n';
    std::cout << "TypeTaged h2 = " << type2.getTypeTaged<Health>().value() << '\n';
    std::cout << "TypeTaged 1  = " << (std::string)type2.getTypeTaged<Name>() << '\n';
    std::cout << "TypeTaged 2  = " << (std::string)type2.getTypeTaged<Name, name_t>() << '\n';

    std::cout << name<decltype(type2.getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged<struct x>())>() << '\n';
    std::cout << name<decltype(type2.getTaged())>() << '\n';
    std::cout << name<decltype(std::as_const(type2).getTaged())>() << '\n'
              << '\n';

    std::cout << parse_type_name<general_type>() << '\n';
    std::cout << parse_type_name<general_type2>() << '\n';

    {
        auto print_num = []<size_t NUM, typename T>(T& t) {
            if constexpr (T::template haveTypeNum<NUM>()) {
                auto value = t.template getType<NUM>();
                std::print("type[{}] = [{}] {}\n", NUM, name<decltype(value)>(), value);
            }
        };

        print_num.operator()<0>(type2);
        print_num.operator()<1>(type2);
        print_num.operator()<2>(type2);
        print_num.operator()<3>(type2);
        print_num.operator()<4>(type2);
        print_num.operator()<5>(type2);
        print_num.operator()<6>(type2);
        print_num.operator()<7>(type2);
        print_num.operator()<8>(type2);
        print_num.operator()<9>(type2);
    }

    {
        using featured_general_type2 = GeneralFeatures<general_type2>;

        featured_general_type2 feature_type2;
        feature_type2.getType<Protection, 0>() = Protection{10};
        // std::cout << parse_type_name<featured_general_type2>() << '\n';
    }

    static_assert(not is_property<GeneralFeatures>);
}