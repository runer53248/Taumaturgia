#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/improved_types.hpp"
#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"

using helpers::create_ordered_property_list;
using helpers::is_same_priority;

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
    static_assert(Property_ordered<Living>::value < Property_ordered<Damaging>::value);
    static_assert(Property_ordered<Damaging>::value < Property_ordered<Protecting>::value);
    static_assert(Property_ordered<Protecting>::value < Property_ordered<A>::value);
    static_assert(Property_ordered<A>::value == Property_ordered<B>::value);
    static_assert(std::is_same_v<
                  type_0,
                  list<
                      Property_ordered<Living>,
                      Property_ordered<Damaging>,
                      Property_ordered<Protecting>,
                      Property_ordered<A>,
                      Property_ordered<B>>>);

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
    std::cout << "3) checking removing of duplicates and reorder rest" << '\n';
    std::cout << name<type_1>() << '\n';
    std::cout << name<type_2>() << '\n';
    std::cout << '\n';

    using type_3 = create_ordered_property_list<A, B, Protecting, Living, Damaging>;
    using type_4 = create_ordered_property_list<B, A, Protecting, Damaging, Living>;
    static_assert(not std::is_same_v<type_3, type_4>);  // checking removing of unknown properties and reorder
    std::cout << "4) checking ignoring order of unknown properties and reorder rest" << '\n';
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

    using type_x0 = create_ordered_property_list<Damaging, DamagingImproved, Damaging_impl, DamagingImproved_>;
    using type_x1 = create_ordered_property_list<Damaging_impl, DamagingImproved, Damaging, DamagingImproved_>;
    using type_x2 = create_ordered_property_list<DamagingImproved_, Damaging_impl, DamagingImproved, Damaging>;
    using type_y0 = create_ordered_property_list<DamagingImproved, Damaging, Damaging_impl, DamagingImproved_>;
    using type_y1 = create_ordered_property_list<DamagingImproved, Damaging_impl, Damaging, DamagingImproved_>;
    using type_y2 = create_ordered_property_list<DamagingImproved_, DamagingImproved, Damaging_impl, Damaging>;
    static_assert(std::is_same_v<type_x0, list<Property_ordered<Damaging>>>);
    static_assert(std::is_same_v<type_x1, list<Property_ordered<Damaging_impl>>>);
    static_assert(std::is_same_v<type_x2, list<Property_ordered<DamagingImproved_>>>);
    static_assert(std::is_same_v<type_y0, list<Property_ordered<DamagingImproved>>>);
    static_assert(std::is_same_v<type_y1, list<Property_ordered<DamagingImproved>>>);
    static_assert(std::is_same_v<type_y2, list<Property_ordered<DamagingImproved_>>>);
    std::cout << "8) only first occurence of same property index count in create_ordered_property_list" << '\n';
    std::cout << name<type_x0>() << '\n';
    std::cout << name<type_x1>() << '\n';
    std::cout << name<type_x2>() << '\n';
    std::cout << name<type_y0>() << '\n';
    std::cout << name<type_y1>() << '\n';
    std::cout << name<type_y2>() << '\n'
              << '\n';

    static_assert(Property_ordered<Protecting_impl>::value == Property_ordered<Protecting>::value);
    static_assert(is_same_priority<Property_ordered<Protecting_impl>, Property_ordered<Protecting>>);
    static_assert(Property_ordered<Damaging_impl>::value == Property_ordered<Damaging>::value);
    static_assert(is_same_priority<Property_ordered<Damaging_impl>, Property_ordered<Damaging>>);

    using type_x = create_ordered_property_list<Protecting_impl, Damaging_impl, Protecting, Damaging>;  // end with Protecting, Damaging
    using type_y = create_ordered_property_list<Damaging_impl, Protecting_impl, Damaging, Protecting>;  // end with Damaging, Protecting
    std::cout << "9) user created properties with same encapsulated type don't count as build-in ones (ie. not have its index)" << '\n';
    std::cout << name<type_x>() << '\n';
    std::cout << name<type_y>() << '\n'
              << '\n';

    using type_a = create_ordered_property_list<Damaging, Damaging_impl>;  // only Damaging
    using type_b = create_ordered_property_list<Damaging_impl, Damaging>;  // only Damaging_impl
    static_assert(not std::is_same_v<type_a, type_b>);
    std::cout << "10) build-in property and its conditional variant are distinque" << '\n';
    std::cout << name<type_a>() << '\n';
    std::cout << name<type_b>() << '\n'
              << '\n';

    using type_c = create_ordered_property_list<Damaging_impl, Living, Damaging>;
    using type_d = create_ordered_property_list<Living, Damaging_impl, Damaging>;
    static_assert(std::is_same_v<type_c, type_d>);
    std::cout << name<type_c>() << '\n';
    std::cout << name<type_d>() << '\n'
              << '\n';

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
