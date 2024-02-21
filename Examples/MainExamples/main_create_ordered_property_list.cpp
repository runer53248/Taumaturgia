#include "../basic_strategies.hpp"
#include "../demangle_type_name.hpp"
#include "../is_base_of_template.hpp"
#include "../property_A.hpp"
#include "../property_B.hpp"
#include "Examples/preety_print.hpp"

template <typename T>
struct DamagingImproved : T {
    using property_data = PropertyData<impl::damaging_type_name, DamagingImproved, T>;
    using improvement_of = impl::Damaging_<T>;

    DamagingImproved() = default;
};

#include "../../Object/Properties/UserProperty.hpp"

template <typename T>
using UserDamaging = UserProperty<Damage, T>;
template <typename T>
using UserProtecting = UserProperty<Protection, T>;

template <typename T>
struct UserProtectingImproved : T {
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved, T>;
    using improvement_of = UserProtecting<T>;

    UserProtectingImproved() = default;
};

template <typename T>
struct UserProtectingImproved_2 : T {
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved_2, T>;
    using improvement_of = UserProtecting<T>;

    UserProtectingImproved_2() = default;
};

int main() {
    std::cout << "A. 'create_ordered_property_list' examples:" << '\n'
              << '\n';

    std::cout << "1) create_ordered_property_list<A, B, Protecting, A, Protecting, Living, Damaging, A>" << '\n';
    using type_0 = create_ordered_property_list<
        A,
        B,
        Protecting,
        A,
        Protecting,
        Living,
        Damaging,
        A>;
    std::cout << name<type_0>() << '\n'
              << '\n';
    static_assert(Property<Living>::value < Property<Damaging>::value);
    static_assert(Property<Damaging>::value < Property<Protecting>::value);
    static_assert(Property<Protecting>::value < Property<A>::value);
    static_assert(Property<A>::value == Property<B>::value);
    static_assert(std::is_same_v<
                  type_0,
                  list<
                      Property<Living>,
                      Property<Damaging>,
                      Property<Protecting>,
                      Property<A>,
                      Property<B>>>);

    using type_00 = create_ordered_property_list<Damaging, Protecting>;
    using type_01 = create_ordered_property_list<Protecting, Damaging>;
    static_assert(std::is_same_v<type_00, type_01>);  // checking reorder

    std::cout << "2) checking reorder" << '\n';
    std::cout << name<type_00>() << '\n';
    std::cout << name<type_01>() << '\n';
    std::cout << '\n';

    using type_1 = create_ordered_property_list<Damaging, Damaging, Living, Damaging>;
    using type_2 = create_ordered_property_list<Living, Damaging>;
    static_assert(std::is_same_v<type_1, type_2>);  // checking removing of duplicates and reorder
    std::cout << "3) checking removing of duplicates and reorder" << '\n';
    std::cout << name<type_1>() << '\n';
    std::cout << name<type_2>() << '\n';
    std::cout << '\n';

    using type_3 = create_ordered_property_list<A, B, Protecting, Living, Damaging>;
    using type_4 = create_ordered_property_list<B, A, Protecting, Damaging, Living>;
    static_assert(not std::is_same_v<type_3, type_4>);  // checking removing of unknown properties and reorder
    std::cout << "4) checking ignoring order of unknown properties and reorder" << '\n';
    std::cout << name<type_3>() << '\n';
    std::cout << name<type_4>() << '\n';
    std::cout << '\n';

    using type_5 = create_ordered_property_list<A, Wearing, B, Protecting, A, Restoring, Naming, Living, Damaging, Healing, A>;
    using type_6 = create_ordered_property_list<Restoring, B, A, Living, Healing, Protecting, Protecting, Damaging, Protecting, Wearing, Living, Naming, Protecting>;
    using type_6b = create_ordered_property_list<Restoring, A, B, Living, Healing, Protecting, Protecting, Damaging, Protecting, Wearing, Living, Naming, Protecting>;
    static_assert(not std::is_same_v<type_5, type_6>);  // checking all properties (unorder of A and B)
    static_assert(std::is_same_v<type_5, type_6b>);     // checking all properties
    std::cout << "5) checking all properties" << '\n';
    std::cout << name<type_5>() << '\n';
    std::cout << name<type_6>() << '\n';
    std::cout << name<type_6b>() << '\n';
    std::cout << '\n';

    std::cout << "6) checking no properties" << '\n';
    using type_7 = create_ordered_property_list<>;
    std::cout << name<type_7>() << " - no properties" << '\n';  // no properties
    std::cout << '\n';

    std::cout << "7) checking unknown properties only" << '\n';
    using type_8 = create_ordered_property_list<A, B>;
    using type_9 = create_ordered_property_list<B, A>;
    static_assert(not std::is_same_v<type_8, type_9>);
    std::cout << name<type_8>() << " - all properties are unknown" << '\n';  // all properties are unknown
    std::cout << name<type_9>() << " - all properties are unknown" << '\n';  // all properties are unknown
    std::cout << '\n';

    //////////////////////

    static_assert(Property<Damaging>::value == Property<impl::Damaging_>::value);
    static_assert(same_priority<Property<Damaging>, Property<impl::Damaging_>>::value);

    // improvements of properties
    static_assert(Property<Damaging>::value == Property<DamagingImproved>::value);
    static_assert(same_priority<Property<Damaging>, Property<DamagingImproved>>::value);
    static_assert(same_priority<Property<impl::Damaging_>, Property<DamagingImproved>>::value);
    std::cout << "build-in properties can be improved" << '\n';
    std::cout << "Damaging priority = " << Property<Damaging>::value << '\n';
    std::cout << "impl::Damaging_ priority = " << Property<impl::Damaging_>::value << '\n';
    std::cout << "DamagingImproved priority = " << Property<DamagingImproved>::value << '\n'
              << '\n';

    using type_x0 = create_ordered_property_list<Damaging, DamagingImproved, impl::Damaging_>;
    using type_x1 = create_ordered_property_list<impl::Damaging_, DamagingImproved, Damaging>;
    using type_y0 = create_ordered_property_list<DamagingImproved, Damaging, impl::Damaging_>;
    using type_y1 = create_ordered_property_list<DamagingImproved, impl::Damaging_, Damaging>;
    std::cout << "only first occurence of similiar type count in create_ordered_property_list" << '\n';
    std::cout << name<type_x0>() << '\n';
    std::cout << name<type_x1>() << '\n';
    std::cout << name<type_y0>() << '\n';
    std::cout << name<type_y1>() << '\n'
              << '\n';

    // improvements of user properties
    static_assert(Property<UserProtectingImproved>::value == Property<UserProtecting>::value);
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtecting>>::value);            // ? same_priority
    static_assert(same_priority<Property<UserProtecting>, Property<UserProtectingImproved>>::value);            // ? same_priority
    static_assert(same_priority<Property<UserProtectingImproved>, Property<UserProtectingImproved_2>>::value);  // ? same_priority

    // UserProperty may have same priority value but are not considered same by same_priority struct
    static_assert(Property<UserProtecting>::value == Property<UserDamaging>::value);            // same priority value
    static_assert(not same_priority<Property<UserProtecting>, Property<UserDamaging>>::value);  // not same_priority

    // user created properties with same encapsulated type don't count as build-in ones
    static_assert(Property<UserProtecting>::value != Property<Protecting>::value);
    static_assert(Property<UserDamaging>::value != Property<Damaging>::value);
    static_assert(not same_priority<Property<UserProtecting>, Property<Protecting>>::value);
    static_assert(not same_priority<Property<UserDamaging>, Property<Damaging>>::value);
    using type_x = create_ordered_property_list<UserProtecting, UserDamaging, Protecting, Damaging>;
    using type_y = create_ordered_property_list<UserDamaging, UserProtecting, Damaging, Protecting>;
    std::cout << "user created properties with same encapsulated type don't count as build-in ones" << '\n';
    std::cout << name<type_x>() << '\n';
    std::cout << name<type_y>() << '\n'
              << '\n';

    using type_a = create_ordered_property_list<Damaging, impl::Damaging_>;  // only Damaging
    using type_b = create_ordered_property_list<impl::Damaging_, Damaging>;  // only impl::Damaging_
    static_assert(not std::is_same_v<type_a, type_b>);
    std::cout << name<type_a>() << '\n';
    std::cout << name<type_b>() << '\n'
              << '\n';

    struct Type {
    public:
        Damage dmgs;
        Damage dmg;
    };
    std::cout << name<Damaging<Type>>() << '\n';
    std::cout << name<impl::Damaging_<Type>>() << '\n';
    // impl::Damaging_<Type>{}.dmg; // public dmg is shadowed by private one from Damaging_
    impl::Damaging_<Type>{}.dmgs;
    std::cout << name<UserDamaging<Type>>() << '\n'
              << '\n';

    using type_c = create_ordered_property_list<impl::Damaging_, Living, Damaging>;
    using type_d = create_ordered_property_list<Living, impl::Damaging_, Damaging>;
    static_assert(std::is_same_v<type_c, type_d>);

    return 0;
}
