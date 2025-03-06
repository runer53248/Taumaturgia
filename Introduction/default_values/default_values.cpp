#include <print>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Base {};
struct int_tag;
struct float_tag;
struct name_tag;
struct protection_tag;

constexpr auto default_int = 5;
constexpr auto default_int2 = 33;
constexpr auto default_float = 3.1416f;

template <>
struct UserDefaultValue<int> {
    static constexpr auto value = [] { return default_int; };
};
template <>
struct UserDefaultValue<int, int_tag> {
    static constexpr auto value = [] { return default_int2; };
};
template <>
struct UserDefaultValue<float, float_tag> {
    static constexpr auto value = [] { return default_float; };
};
template <>
struct UserDefaultValue<std::string, name_tag> {
    static constexpr auto value = [] { return "Andre"; };
};

template <>
struct UserDefaultValue<Health> {
    static constexpr auto value = [] { return Health{150}; };
};
template <>
struct UserDefaultValue<Damage> {
    static constexpr auto value = [] { return Damage{30, DamageType::Magical}; };
};
template <>
struct UserDefaultValue<Protection> {
    static constexpr auto value = [] { return Protection{15, BodyLocation::Body}; };
};

namespace buildin {  // prepare_buildin_defaults objects moves UserDefaultValue into buildin_defaults
prepare_buildin_defaults<Health, Damage, Protection> prepare{};
}  // namespace buildin

int main() {
    using Int_name = list<int, int_tag>;
    using Float_name = list<float, float_tag>;
    using Name = list<std::string, name_tag>;

    constexpr auto x =                       // pipeing with create
        Base{}                               //
        | With::user_property<int>           //
        | With::user_property_t<Int_name>    //
        | With::user_property_t<Float_name>  //
        | Create;
    auto y =                           // pipeing with create
        Base{}                         //
        | With::user_property_t<Name>  //
        | Create;

    static_assert(x.getType<int>() == default_int);
    static_assert(x.getType<int, 1>() == default_int2);
    static_assert(x.getTaged<int_tag>() == default_int2);
    static_assert(x.getTypeOfSignature<Float_name>() == default_float);

    std::print("x.int   = {}\n", x.getType<int>());
    std::print("x.int2  = {}\n", x.getType<int, 1>());
    std::print("x.float = {}\n", x.getType<float>());
    std::print("y.name  = {}\n", y.getTypeOfSignature<Name>());

    {
        auto test =
            Base{}                                             //
            | With::Health                                     //
            | With::Damage                                     //
            | With::user_property<int>                         //
            | With::user_property<int, int_tag>                //
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            // | With::user_property_t<Int_name>  //! don't have trait access
            | Create;

        std::cout << "test.Health     = " << traits::accessHealth::get(test) << "\n";
        std::cout << "test.Damage     = " << traits::accessDamage::get(test) << "\n";
        std::cout << "test.Protection = " << traits::accessProtection::get(test) << "\n";
        std::cout << "test.int        = " << traits::impl::accessType<int>::get(test) << "\n";
        std::cout << "test.Health     = " << trait<Health>::get(test) << "\n";
        std::cout << "test.Damage     = " << trait<Damage>::get(test) << "\n";
        std::cout << "test.Protection = " << trait<Protection>::get(test) << "\n";
        std::cout << "test.Protection2= " << test.getTypeTaged<Protection, protection_tag>() << "\n";
        std::cout << "test.int        = " << trait<int>::get(test) << "\n";

        std::print("{}\n", parse_type_name<decltype(test)>());
        std::print("{}\n\n", ::name<decltype(test)>());
    }

    {
        auto test1 =
            Base{}                                             //
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | Create;
        auto test2 =
            Base{}                                             //
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | Create;
        auto test3 =
            Base{}                                             //
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | Create;
        auto test4 =
            Base{}                                             //
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | Create;
        auto test5 =
            Base{}                                             //
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | Create;
        auto test6 =
            Base{}                                             //
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::user_property<Protection>                  //! may remove buildin Protecting_
            | Create;
        std::print("\n\ntest1 = {}\n", ::name<decltype(test1)>());
        std::print("test2 = {}\n", ::name<decltype(test2)>());
        std::print("test3 = {}\n", ::name<decltype(test3)>());
        std::print("test4 = {}\n", ::name<decltype(test4)>());
        std::print("test5 = {}\n", ::name<decltype(test5)>());
        std::print("test6 = {}\n", ::name<decltype(test6)>());

        auto test7 =
            Base{}                                             //
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | Create;
        auto test8 =
            Base{}                                             //
            | With::Protection                                 //!!! dont work with user_property<Protection,...>
            | With::user_property<Protection, protection_tag>  //! may remove buildin Protecting_
            | Create;
        static_assert(std::same_as<decltype(test7), decltype(test8)>);
        std::print("\ntest7 = {}\n", ::name<decltype(test7)>());
        std::print("test8 = {}\n", ::name<decltype(test8)>());
    }
}
