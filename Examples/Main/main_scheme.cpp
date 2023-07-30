#include <boost/core/demangle.hpp>
#include <typeinfo>
#include "Examples/preety_print.hpp"
#include "basic_strategies.hpp"

template <class T>
std::string name() {
    return boost::core::demangle(typeid(T).name());
}

struct test_struct {};
struct test_struct_2 {};

constexpr char a_type_name[] = "A";

template <typename T>
struct A : T {
    using property_data = PropertyData<A, T, a_type_name>;
};

constexpr char b_type_name[] = "B";

template <typename T>
struct B : T {
    using property_data = PropertyData<B, T, b_type_name>;
};

using WearingIndex = typename Wearing<test_struct>::property_data::property_type;
static_assert(WearingIndex::value == mp_find<order_list, Wearing<tag>>::value + 1);

int main() {
    std::cout << "Compare 2 ways of creating new type by adding properties:\n\n";

    using test_type_bad = Damaging<Living<Naming<test_struct>>>;
    using test_type_new = add_properties<test_struct, Damaging, Living, Naming>;
    std::cout << "properties are: Damaging, Living, Naming \n";
    std::cout << "base:             " << name<Scheme<test_type_bad>::base>() << '\n';
    std::cout << "base_new:         " << name<Scheme<test_type_new>::base>() << '\n';
    std::cout << "list_helper:      " << name<Scheme<test_type_bad>::list_helper>() << '\n';
    std::cout << "list_helper_new:  " << name<Scheme<test_type_new>::list_helper>() << '\n';
    std::cout << "list:             " << name<Scheme<test_type_bad>::list>() << '\n';
    std::cout << "list_new:         " << name<Scheme<test_type_new>::list>() << '\n';
    std::cout << "result_bad:       " << name<test_type_bad>() << '\n';
    std::cout << "result_new:       " << name<test_type_new>() << '\n';
    std::cout << '\n';
    using test_type2_bad = Naming<Damaging<Living<test_struct>>>;
    using test_type2_new = add_properties<test_struct, Naming, Damaging, Living>;
    std::cout << "properties are: Naming, Damaging, Living \n";
    std::cout << "base:             " << name<Scheme<test_type2_bad>::base>() << '\n';
    std::cout << "base_new:         " << name<Scheme<test_type2_new>::base>() << '\n';
    std::cout << "list_helper:      " << name<Scheme<test_type2_bad>::list_helper>() << '\n';
    std::cout << "list_helper_new:  " << name<Scheme<test_type2_new>::list_helper>() << '\n';
    std::cout << "list:             " << name<Scheme<test_type2_bad>::list>() << '\n';
    std::cout << "list_new:         " << name<Scheme<test_type2_new>::list>() << '\n';
    std::cout << "result_bad:       " << name<test_type2_bad>() << '\n';
    std::cout << "result_new:       " << name<test_type2_new>() << '\n';
    std::cout << '\n';
    std::cout << "properties order should be:\n";
    std::cout << Property<Naming>::value << " - Naming priority" << '\n';
    std::cout << Property<Living>::value << " - Living priority" << '\n';
    std::cout << Property<Damaging>::value << " - Damaging priority" << '\n';
    std::cout << '\n';

    static_assert(not std::is_same_v<test_type_bad,
                                     test_type2_bad>);
    static_assert(std::is_same_v<Scheme<test_type_bad>::base,
                                 Scheme<test_type2_bad>::base>);
    static_assert(std::is_same_v<Scheme<test_type_bad>::list,
                                 Scheme<test_type2_bad>::list>);

    static_assert(not std::is_same_v<Damaging<Living<Naming<test_struct>>>,  // ! incorect order
                                     Naming<Damaging<Living<test_struct>>>>);
    static_assert(std::is_same_v<add_properties<test_struct, Damaging, Living, Naming>,  // add_properties can handle ordering
                                 add_properties<test_struct, Naming, Damaging, Living>>);

    std::cout << "Check literals pointers of property_data::name():\n\n";

    static_assert(Naming_<test_struct>::property_data::name() == Naming_<test_struct_2>::property_data::name());
    std::cout << (long long*)Naming_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Naming_<test_struct_2>::property_data::name() << '\n';
    std::cout << Naming_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Living_<test_struct>::property_data::name() == Living_<test_struct_2>::property_data::name());
    std::cout << (long long*)Living_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Living_<test_struct_2>::property_data::name() << '\n';
    std::cout << Living_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Damaging_<test_struct>::property_data::name() == Damaging_<test_struct_2>::property_data::name());
    std::cout << (long long*)Damaging_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Damaging_<test_struct_2>::property_data::name() << '\n';
    std::cout << Damaging_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Protecting_<test_struct>::property_data::name() == Protecting_<test_struct_2>::property_data::name());
    std::cout << (long long*)Protecting_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Protecting_<test_struct_2>::property_data::name() << '\n';
    std::cout << Protecting_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Healing_<test_struct>::property_data::name() == Healing_<test_struct_2>::property_data::name());
    std::cout << (long long*)Healing_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Healing_<test_struct_2>::property_data::name() << '\n';
    std::cout << Healing_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Restoring_<test_struct>::property_data::name() == Restoring_<test_struct_2>::property_data::name());
    std::cout << (long long*)Restoring_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Restoring_<test_struct_2>::property_data::name() << '\n';
    std::cout << Restoring_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Wearing_<test_struct>::property_data::name() == Wearing_<test_struct_2>::property_data::name());
    std::cout << (long long*)Wearing_<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Wearing_<test_struct_2>::property_data::name() << '\n';
    std::cout << Wearing_<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';

    using x_type = add_properties<test_struct, Protecting, Living>;
    std::cout << "x_type:       " << name<x_type>() << '\n';
    std::cout << "base:         " << name<Scheme<x_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<x_type>::list_helper>() << '\n';
    std::cout << "list:         " << name<Scheme<x_type>::list>() << '\n';
    std::cout << '\n';
    using y_type = add_properties<x_type, Wearing, Restoring>;
    std::cout << "y_type:       " << name<y_type>() << " Need to be fixed - should be the same as z_type" << '\n';
    std::cout << "base:         " << name<Scheme<y_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<y_type>::list_helper>() << '\n';
    std::cout << "list:         " << name<Scheme<y_type>::list>() << '\n';
    std::cout << '\n';
    using z_type = add_properties<test_struct, Wearing, Restoring, Protecting, Living>;  // correctly ordered type
    std::cout << "z_type:       " << name<z_type>() << '\n';
    std::cout << "base:         " << name<Scheme<z_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<z_type>::list_helper>() << '\n';
    std::cout << "list:         " << name<Scheme<z_type>::list>() << '\n';
    std::cout << '\n';

    using b_type = add_properties<test_struct, B, Wearing, Restoring, A, A, Protecting, Living, B>;  // correctly ordered type
    std::cout << "b_type:       " << name<b_type>() << '\n';
    std::cout << "base:         " << name<Scheme<b_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<b_type>::list_helper>() << '\n';
    std::cout << "list:         " << name<Scheme<b_type>::list>() << '\n';
    std::cout << '\n';
}
