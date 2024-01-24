#include "Examples/preety_print.hpp"
#include "basic_strategies.hpp"
#include "demangle_type_name.hpp"
#include "is_base_of_template.hpp"
#include "property_A.hpp"
#include "property_B.hpp"

int main() {
    std::cout << "A. 'create_ordered_property_list' examples:" << '\n'
              << '\n';

    std::cout << "1) create_ordered_property_list<A, B, Protecting, A, Protecting, Living, Damaging, A>" << '\n';
    std::cout << name<create_ordered_property_list<
                     A,
                     B,
                     Protecting,
                     A,
                     Protecting,
                     Living,
                     Damaging,
                     A>>()
              << '\n'
              << '\n';

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
    std::cout << name<create_ordered_property_list<>>() << " - no properties" << '\n';  // no properties
    std::cout << '\n';

    std::cout << "7) checking unknown properties only" << '\n';
    std::cout << name<create_ordered_property_list<A, B>>() << " - all properties are unknown" << '\n';  // all properties are unknown
    std::cout << '\n';

    return 0;
}
