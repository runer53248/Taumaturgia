#include <print>
#include "Introduction/parse_type_name.hpp"
#include "Taumaturgia/Properties/GeneralFeatures.hpp"

#include "Examples/PreetyPrint/preety_print.hpp"

struct Type {
    Name name{"Name c"};  // default in base
    Damage dmg{30, DamageType::Divine};
    Health hp;
    int type{500};
};

struct name_t {};
struct int_t {};

template <>
struct UserDefaultValue<Name> {
    static constexpr auto value = [] { return Name{"Name a"}; };
};
template <>
struct UserDefaultValue<Name, name_t> {
    static constexpr auto value = [] { return Name{"Name b"}; };
};
template <>
struct UserDefaultValue<int, int_t> {
    static constexpr auto value = [] { return 133; };
};

int main() {
    prepare_buildin_defaults<Name>();  // sets default for buildin properties

    static_assert(trait_accessable<Type, Name>);
    static_assert(trait_accessable<Type, Damage>);
    static_assert(trait_accessable<Type, Health>);
    static_assert(trait_accessable<Type, int>);

    using property_health_x = Property<UserPropertyAdapter<Health, struct x>::apply>;
    using property_name_name_t = Property<UserPropertyAdapter<Name, name_t>::apply>;
    using property_int_int_t = Property<UserPropertyAdapter<int, int_t>::apply>;
    using property_name = Property<Naming_impl>;
    using property_protection = Property<Protecting_impl>;

    using general_type = GeneralFeatures<Type>;
    using general_type2 = add_properties<general_type,
                                         property_health_x,
                                         property_name_name_t,
                                         property_int_int_t,
                                         property_name,
                                         property_protection>;

    static_assert(trait_accessable<general_type, Name>);
    static_assert(trait_accessable<general_type, Damage>);
    static_assert(trait_accessable<general_type, Health>);

    static_assert(trait_accessable<general_type2, Name>);
    static_assert(trait_accessable<general_type2, Damage>);
    static_assert(trait_accessable<general_type2, Health>);
    static_assert(trait_accessable<general_type2, Protection>);
    static_assert(not trait_accessable<general_type2, CureHealth>);

    {
        general_type type;

        // 1 GeneralFeatures_<>::getTaged
        {
            // TODO: getTaged for eg. int
            static_assert(std::same_as<decltype(type.getTaged()), Name&>);
            static_assert(std::same_as<decltype(type.getTaged<1>()), Damage&>);
            static_assert(std::same_as<decltype(type.getTaged<2>()), Health&>);
            static_assert(std::same_as<decltype(type.getTaged<3>()), void>);  // !  int unreachable
            static_assert(std::same_as<decltype(type.getTaged<x>()), void>);
            static_assert(std::same_as<decltype(std::as_const(type).getTaged<x>()), void>);
            static_assert(std::same_as<decltype(std::as_const(type).getTaged()), const Name&>);
        }

        // 2 GeneralFeatures_<>::getType
        {
            static_assert(std::same_as<decltype(type.getType<Name>()), Name&>);
            static_assert(std::same_as<decltype(type.getType<Damage>()), Damage&>);
            static_assert(std::same_as<decltype(type.getType<Health>()), Health&>);
            static_assert(std::same_as<decltype(type.getType<int>()), int&>);

            static_assert(std::same_as<decltype(type.getType<Name, 1>()), void>);

            static_assert(std::same_as<decltype(std::as_const(type).getType<Name>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type).getType<Name, 1>()), void>);
        }

        // 3 GeneralFeatures_<>::getTypeTaged
        {
            static_assert(std::same_as<decltype(type.getTypeTaged<Name>()), Name&>);
            static_assert(std::same_as<decltype(type.getTypeTaged<Damage>()), Damage&>);
            static_assert(std::same_as<decltype(type.getTypeTaged<Health>()), Health&>);
            static_assert(std::same_as<decltype(type.getTypeTaged<int>()), int&>);

            // static_assert(std::same_as<decltype(type.getTypeTaged<Damage, int_t>()), void>);  // *wrong tag
        }

        // 4 GeneralFeatures_<>::getTypeOf
        {
            static_assert(std::same_as<decltype(type.getTypeOf(list<Name>{})), Name&>);
            static_assert(std::same_as<decltype(type.getTypeOf(list<Damage>{})), Damage&>);
            static_assert(std::same_as<decltype(type.getTypeOf(list<Health>{})), Health&>);
            static_assert(std::same_as<decltype(type.getTypeOf(list<int>{})), int&>);

            // static_assert(std::same_as<decltype(type.getTypeOf(list<Damage, int_t>{})), void>);  // *wrong tag
        }

        // 5 GeneralFeatures_<>::getTypeOfSignature
        {
            static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Name>>()), Name&>);
            static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage>>()), Damage&>);
            static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Health>>()), Health&>);
            static_assert(std::same_as<decltype(type.getTypeOfSignature<list<int>>()), int&>);

            // static_assert(std::same_as<decltype(type.getTypeOfSignature<list<Damage, int_t>>()), void>);  // *wrong tag
        }
    }

    {
        general_type2 type2;

        [[maybe_unused]] auto t1 = type2.getTypeTaged<Protection>();
        [[maybe_unused]] auto t2 = type2.getTypeTaged<Name>();
        general_type t;
        [[maybe_unused]] auto t3 = t.getTypeTaged<Name>();
        UserProperty<int, general_type> tt;
        [[maybe_unused]] auto t4 = tt.getTypeTaged<Name>();

        // 1 Features_<>::getTaged
        {
            // TODO: getTaged for eg. int
            static_assert(std::same_as<decltype(type2.getTaged()), Protection&>);
            static_assert(std::same_as<decltype(type2.getTaged<1>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTaged<x>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTaged<name_t>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTaged<int_t>()), int&>);
            static_assert(std::same_as<decltype(type2.getTaged<2>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTaged<3>()), Damage&>);
            static_assert(std::same_as<decltype(type2.getTaged<4>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTaged<5>()), void>);

            static_assert(std::same_as<decltype(std::as_const(type2).getTaged()), const Protection&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<1>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<x>()), const Health&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<name_t>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<int_t>()), const int&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<2>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<3>()), const Damage&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<4>()), const Health&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getTaged<5>()), void>);

            static_assert(&type2.getType<0>() == &type2.getTaged<>());
            static_assert(&type2.getType<1>() == &type2.getTaged<1>());
            static_assert(&type2.getType<2>() == &type2.getTaged<x>());
            static_assert(&type2.getType<3>() == &type2.getTaged<name_t>());
            static_assert(&type2.getType<4>() == &type2.getTaged<int_t>());
            static_assert(&type2.getType<5>() == &type2.getTaged<2>());
            static_assert(&type2.getType<6>() == &type2.getTaged<3>());
            static_assert(&type2.getType<7>() == &type2.getTaged<4>());
            // static_assert(&type2.getType<8>() == &type2.getTaged<5>()); // !
        }
        // 2 Features_<>::getType
        {
            static_assert(std::same_as<decltype(type2.getType<Protection>()), Protection&>);
            static_assert(std::same_as<decltype(type2.getType<Name, 0>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<Health, 0>()), Health&>);
            static_assert(std::same_as<decltype(type2.getType<Name, 1>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<int, 0>()), int&>);
            static_assert(std::same_as<decltype(type2.getType<Name, 2>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<Damage>()), Damage&>);
            static_assert(std::same_as<decltype(type2.getType<Health, 1>()), Health&>);
            static_assert(std::same_as<decltype(type2.getType<int, 1>()), int&>);
            static_assert(std::same_as<decltype(type2.getType<Name, 3>()), void>);  // non existing

            static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 0>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 1>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 2>()), const Name&>);
            static_assert(std::same_as<decltype(std::as_const(type2).getType<Name, 3>()), void>);  // non existing

            static_assert(&type2.getType<0>() == &type2.getType<Protection>());
            static_assert(&type2.getType<1>() == &type2.getType<Name, 0>());
            static_assert(&type2.getType<2>() == &type2.getType<Health, 0>());
            static_assert(&type2.getType<3>() == &type2.getType<Name, 1>());
            static_assert(&type2.getType<4>() == &type2.getType<int, 0>());
            static_assert(&type2.getType<5>() == &type2.getType<Name, 2>());
            static_assert(&type2.getType<6>() == &type2.getType<Damage>());
            static_assert(&type2.getType<7>() == &type2.getType<Health, 1>());
            static_assert(&type2.getType<8>() == &type2.getType<int, 1>());
        }
        // 2.1 Features_<>::getType new kind
        {
            static_assert(std::same_as<decltype(type2.getType<0>()), Protection&>);
            static_assert(std::same_as<decltype(type2.getType<1>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<2>()), Health&>);
            static_assert(std::same_as<decltype(type2.getType<3>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<4>()), int&>);
            static_assert(std::same_as<decltype(type2.getType<5>()), Name&>);
            static_assert(std::same_as<decltype(type2.getType<6>()), Damage&>);
            static_assert(std::same_as<decltype(type2.getType<7>()), Health&>);
            static_assert(std::same_as<decltype(type2.getType<8>()), int&>);
            // static_assert(std::same_as<decltype(type2.getType<9>()), void>);
        }
        // 3 Features_<>::getTypeTaged
        {
            static_assert(std::same_as<decltype(type2.getTypeTaged<Protection>()), Protection&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<Name>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<Health, x>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<Name, name_t>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<int, int_t>()), int&>);
            // * second getTypeTaged<Name> - unreachable from getTypeTaged
            static_assert(std::same_as<decltype(type2.getTypeTaged<Damage>()), Damage&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<Health>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeTaged<int>()), int&>);

            // static_assert(std::same_as<decltype(type2.getTypeTaged<Damage, name_t>()), void>);  // *wrong tag

            static_assert(&type2.getType<0>() == &type2.getTypeTaged<Protection>());
            static_assert(&type2.getType<1>() == &type2.getTypeTaged<Name>());
            static_assert(&type2.getType<2>() == &type2.getTypeTaged<Health, x>());
            static_assert(&type2.getType<3>() == &type2.getTypeTaged<Name, name_t>());
            static_assert(&type2.getType<4>() == &type2.getTypeTaged<int, int_t>());
            // * 5 second Name - unreachable
            static_assert(&type2.getType<6>() == &type2.getTypeTaged<Damage>());
            static_assert(&type2.getType<7>() == &type2.getTypeTaged<Health>());
            static_assert(&type2.getType<8>() == &type2.getTypeTaged<int>());
        }
        // 4 Features_<>::getTypeOf
        {
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Protection>{})), Protection&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Name>{})), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Health, x>{})), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Name, name_t>{})), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<int, int_t>{})), int&>);
            // * 5 second list<Name> - unreachable
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Damage>{})), Damage&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<Health>{})), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeOf(list<int>{})), int&>);

            // static_assert(std::same_as<decltype(type2.getTypeOf(list<Damage, int_t>{})), void>);  // *wrong tag

            static_assert(&type2.getType<0>() == &type2.getTypeOf(list<Protection>{}));
            static_assert(&type2.getType<1>() == &type2.getTypeOf(list<Name>{}));
            static_assert(&type2.getType<2>() == &type2.getTypeOf(list<Health, x>{}));
            static_assert(&type2.getType<3>() == &type2.getTypeOf(list<Name, name_t>{}));
            static_assert(&type2.getType<4>() == &type2.getTypeOf(list<int, int_t>{}));
            // * 5 second Name - unreachable
            static_assert(&type2.getType<6>() == &type2.getTypeOf(list<Damage>{}));
            static_assert(&type2.getType<7>() == &type2.getTypeOf(list<Health>{}));
            static_assert(&type2.getType<8>() == &type2.getTypeOf(list<int>{}));
        }
        // 5 Features_<>::getTypeOfSignature
        {
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Protection>>()), Protection&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Name>>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Health, x>>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Name, name_t>>()), Name&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<int, int_t>>()), int&>);
            // * 5 second list<Name> - unreachable
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Damage>>()), Damage&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Health>>()), Health&>);
            static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<int>>()), int&>);

            // static_assert(std::same_as<decltype(type2.getTypeOfSignature<list<Damage, int_t>>()), void>);  // *wrong tag

            static_assert(&type2.getType<0>() == &type2.getTypeOfSignature<list<Protection>>());
            static_assert(&type2.getType<1>() == &type2.getTypeOfSignature<list<Name>>());
            static_assert(&type2.getType<2>() == &type2.getTypeOfSignature<list<Health, x>>());
            static_assert(&type2.getType<3>() == &type2.getTypeOfSignature<list<Name, name_t>>());
            static_assert(&type2.getType<4>() == &type2.getTypeOfSignature<list<int, int_t>>());
            // * 5 second Name - unreachable
            static_assert(&type2.getType<6>() == &type2.getTypeOfSignature<list<Damage>>());
            static_assert(&type2.getType<7>() == &type2.getTypeOfSignature<list<Health>>());
            static_assert(&type2.getType<8>() == &type2.getTypeOfSignature<list<int>>());
        }
    }

    {
        general_type2 type2;

        std::print("type2 0 = {}\n", (std::string)type2.getType<Name, 0>());
        std::print("type2 1 = {}\n", (std::string)type2.getType<Name, 1>());
        std::println("type2 2 = {}\n", (std::string)type2.getType<Name, 2>());

        type2.getType<Name, 0>() = Name{"Name 1"};
        type2.getType<Name, 1>() = Name{"Name 2"};
        type2.getType<Name, 2>() = Name{"Name 3"};
        type2.getType<Protection, 0>() = Protection{10};
        type2.getType<Health, 0>() = Health{100};
        type2.getType<Health, 1>() = Health{200};

        std::print("type2 0 = {}\n", (std::string)type2.getType<Name, 0>());
        std::print("type2 1 = {}\n", (std::string)type2.getType<Name, 1>());
        std::println("type2 2 = {}\n", (std::string)type2.getType<Name, 2>());

        std::print("taged 1 = {}\n", (std::string)type2.getTaged<1>());
        std::println("taged 2 = {}\n", (std::string)type2.getTaged<2>());

        std::print("TypeTaged p  = {}\n", type2.getTypeTaged<Protection>().armorClass());
        std::print("TypeTaged h1 = {}\n", type2.getTypeTaged<Health, x>().value());
        std::print("TypeTaged h2 = {}\n", type2.getTypeTaged<Health>().value());
        std::print("TypeTaged 1  = {}\n", (std::string)type2.getTypeTaged<Name>());
        std::print("TypeTaged 2  = {}\n", (std::string)type2.getTypeTaged<Name, name_t>());

        std::print("{}\n", name<decltype(type2.getTaged<struct x>())>());
        std::print("{}\n", name<decltype(std::as_const(type2).getTaged<struct x>())>());
        std::print("{}\n", name<decltype(type2.getTaged())>());
        std::println("{}\n", name<decltype(std::as_const(type2).getTaged())>());

        std::print("{}\n", parse_type_name<general_type>());
        std::print("{}\n", parse_type_name<general_type2>());

        {
            auto print_num = []<size_t NUM, typename T>(T& t) {
                if constexpr (T::template haveTypeNum<NUM>()) {
                    decltype(auto) value = t.template getType<NUM>();
                    std::print("type[{}] = [{}] {}\n",
                               NUM,
                               name<decltype(value)>(),
                               value);
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
    }

    {
        using featured_general_type2 = GeneralFeatures<general_type2>;

        featured_general_type2 feature_type2;
        feature_type2.getType<Protection, 0>() = Protection{10};
        // std::cout << parse_type_name<featured_general_type2>() << '\n';
    }

    static_assert(not is_property<GeneralFeatures>);
}