#include <print>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

#include <functional>

struct Base {};
struct int_tag;
struct protection_tag;

constexpr auto default_int = 5;
constexpr auto default_int2 = 33;
constexpr auto default_health = Health{150};
constexpr auto default_damage = Damage{30, DamageType::Magical};
const auto default_protection = Protection{15, BodyLocation::Body};
const auto default_protection_tag = Protection{30, BodyLocation::Head};

const auto default_protecting = Protection{5, BodyLocation::Legs};
constexpr auto default_damaging = Damage{30, DamageType::Divine};

template <>
struct UserDefaultValue<int> {
    static constexpr auto value = [] { return default_int; };
};
template <>
struct UserDefaultValue<int, int_tag> {
    static constexpr auto value = [] { return default_int2; };
};

template <>
struct UserDefaultValue<Health> {
    static constexpr auto value = [] { return default_health; };
};
template <>
struct UserDefaultValue<Damage> {
    static constexpr auto value = [] { return default_damage; };
};

template <>
struct UserDefaultValue<Protection> {
    static inline std::move_only_function<Protection()> value = [] { return default_protection; };
};

template <>
struct UserDefaultValue<Protection, protection_tag> {
    static inline std::move_only_function<Protection()> value = [] { return default_protection_tag; };
};

// template <>
// UserDefaultValue<Protection, protection_tag>::func
//     UserDefaultValue<Protection, protection_tag>::value = [] { return default_protection_tag; };

int main() {
    prepare_buildin_defaults<Health, Damage, Protection>();  // ! it will overide set values
    buildin_defaults<Protection>::set(default_protecting);
    buildin_defaults<Damage>::set(default_damaging);

    auto test =
        Base{}                                             //
        | With::Health                                     //
        | With::Damage                                     //
        | With::user_property<int>                         //
        | With::user_property<int, int_tag>                //! don't have trait access
        | With::user_property<Protection>                  //
        | With::user_property<Protection, protection_tag>  //! don't have trait access
        | With::Protection                                 //
        // | With::user_property<bool>                       //
        // | With::user_property<bool,int_tag>                       //
        // | With::user_property<int, int_tag, int>                       //
        // | With::user_property_t<Int_name>  //! don't have trait access
        | Create;

    std::print("test.Health     = {}\n", traits::accessHealth::get(test));
    std::print("test.Damage     = {}\n", traits::accessDamage::get(test));
    std::print("test.Protection = {}\n", traits::accessProtection::get(test));
    std::print("test.int        = {}\n\n", traits::accessType<int>::get(test));

    std::print("test.Health     = {}\n", trait<Health>::get(test));
    std::print("test.Damage     = {}\n", trait<Damage>::get(test));
    std::print("test.Protection = {}\n", trait<Protection>::get(test));
    std::print("test.Protection2= {}\n", test.getTypeTaged<Protection, protection_tag>());
    std::print("test.int        = {}\n", trait<int>::get(test));
    std::print("test.int2       = {}\n\n", test.getTypeTaged<int, int_tag>());

    std::print("test.Protection[0] = {}\n", test.getType<Protection, 0>());
    std::print("test.Protection[1] = {}\n", test.getType<Protection, 1>());
    if constexpr (constexpr bool have = decltype(test)::haveTypeNum<Protection, 2>()) {
        std::print("test.Protection[2] = {}\n", test.getType<Protection, have * 2>());
    }
    std::println();

    auto print_num = []<size_t NUM, typename T>(T& t) {
        if constexpr (T::template haveTypeNum<NUM>()) {
            std::print("{} ", (void*)&(t.template getType<NUM>()));
            std::print("type[{}] = {}\n", NUM, t.template getType<NUM>());
        }
    };

    print_num.operator()<0>(test);
    print_num.operator()<1>(test);
    print_num.operator()<2>(test);
    print_num.operator()<3>(test);
    print_num.operator()<4>(test);
    print_num.operator()<5>(test);
    print_num.operator()<6>(test);

    constexpr bool have_idx_5 = decltype(test)::haveTypeNum<5>();
    constexpr bool have_idx_6 = decltype(test)::haveTypeNum<6>();
    std::print("idx 5  = {}\n", have_idx_5);
    std::print("idx 6  = {}\n", have_idx_6);

    // std::print("test p = {}\n", test.getProtection());  // ! not accessable otherwise
    // TODO: fix it

    std::print("{}\n", parse_type_name<decltype(test)>());
    std::print("{}\n\n", ::name<decltype(test)>());

    std::print("size of test type  = {}\n", sizeof(decltype(test)));
    auto sum_of_prop = sizeof(Health)         //
                       + sizeof(Damage)       //
                       + sizeof(Protection)   //
                       + sizeof(int)          //
                       + sizeof(int)          //
                       + sizeof(Protection);  //
    if constexpr (have_idx_6) {
        sum_of_prop += sizeof(Protection);
    }
    std::print("SUM of prop        = {}\n", sum_of_prop);
    std::print("size of Health     = {} = {}\n",
               sizeof(Health),
               (ptrdiff_t)(sizeof(decltype(test)))    // size of type
                   - (ptrdiff_t)(                     //
                         (char*)(&test.getType<0>())  // position of last property data
                         - (char*)(&test))            // begining of type
    );

    auto address_of_property_0 = (char*)&test.getType<0>();
    auto address_of_property_1 = (char*)&test.getType<1>();
    auto address_of_property_2 = (char*)&test.getType<2>();
    auto address_of_property_3 = (char*)&test.getType<3>();
    auto address_of_property_4 = (char*)&test.getType<4>();
    auto address_of_property_5 = (char*)&test.getType<5>();

    std::print("size of Damage     = {} = {}\n", sizeof(Damage), (ptrdiff_t)(address_of_property_0 - address_of_property_1));
    std::print("size of Protection = {} = {}\n", sizeof(Protection), (ptrdiff_t)(address_of_property_1 - address_of_property_2));
    std::print("size of int        = {} = {}\n", sizeof(int), (ptrdiff_t)(address_of_property_2 - address_of_property_3));
    std::print("size of int        = {} = {}\n", sizeof(int), (ptrdiff_t)(address_of_property_3 - address_of_property_4));
    std::print("size of Protection = {} = {}\n", sizeof(Protection), (ptrdiff_t)(address_of_property_4 - address_of_property_5));

    if constexpr (have_idx_6) {
        auto address_of_property_6 = (char*)&test.getType<have_idx_6 * 6>();
        std::print("size of Protection = {} = {}\n", sizeof(Protection), (ptrdiff_t)(address_of_property_5 - address_of_property_6));
    }
    std::println();
}

// Living_<
//     Damaging_<
//         Protecting_<
//             up_<int,
//                 up_<int,
//                     up_<Protection,
//                         up_<Protection,
//                             Base,
//                             protection_tag>>,
//                     int_tag>>>>>;
// 0 : Living_ : _
// 1 : Damaging_ : _
// 2 : Protecting_ : _ <--- other type in order
// 3 : int : _
// 4 : int : int_tag
// 5 : Protection : _  <--- counts as diffrent type
// 6 : Protection : protection_tag
// -> Base == Base

// up_ = UserProperty_
// up_<Health,
//     up_<Damage,
//         up_<Protection,
//             up_<int,
//                 up_<int,
//                     up_<Protection,
//                         Base,
//                         protection_tag>,
//                     int_tag>>>>>;
// 0 : Health : _
// 1 : Damage : _
// 2 : Protection : _ <---- type in order
// 3 : int : _
// 4 : int : int_tag
//                    <---- duplication missing
// 5 : Protection : protection_tag
// -> Base == Base
