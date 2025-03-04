#include <typeinfo>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"

struct test_struct {};
struct test_struct_2 {};

constinit const char a_type_name[] = "A";

template <typename T>
struct A : public T {
    using property_data = PropertyData<a_type_name, A, T>;
};

constinit const char b_type_name[] = "B";

template <typename T>
class B : public T {
public:
    using property_data = PropertyData<b_type_name, B, T>;
};

using WearingIndex = typename Wearing<test_struct>::property_data::property_type;
static_assert(WearingIndex::value == boost::mp11::mp_find<order_list, Wearing<tag>>::value + 1);

using helpers::Scheme;

int main() {
    std::cout << "Compare 2 ways of creating new type by adding properties:\n\n";

    using test_type_bad = Damaging<Living<Naming<test_struct>>>;
    using test_type_new = add_properties_ordered<test_struct, Damaging, Living, Naming>;
    std::cout << "properties are: Damaging, Living, Naming \n";
    std::cout << "base:             " << name<Scheme<test_type_bad>::base>() << '\n';
    std::cout << "base_new:         " << name<Scheme<test_type_new>::base>() << '\n';
    std::cout << "list_helper:      " << name<Scheme<test_type_bad>::list_helper>() << '\n';
    std::cout << "list_helper_new:  " << name<Scheme<test_type_new>::list_helper>() << '\n';
    std::cout << "list_t:           " << name<Scheme<test_type_bad>::list_t>() << '\n';
    std::cout << "list_new:         " << name<Scheme<test_type_new>::list_t>() << '\n';
    std::cout << "result_bad:       " << name<test_type_bad>() << '\n';
    std::cout << "result_new:       " << name<test_type_new>() << '\n';
    std::cout << '\n';
    using test_type2_bad = Naming<Damaging<Living<test_struct>>>;
    using test_type2_new = add_properties_ordered<test_struct, Naming, Damaging, Living>;
    std::cout << "properties are: Naming, Damaging, Living \n";
    std::cout << "base:             " << name<Scheme<test_type2_bad>::base>() << '\n';
    std::cout << "base_new:         " << name<Scheme<test_type2_new>::base>() << '\n';
    std::cout << "list_helper:      " << name<Scheme<test_type2_bad>::list_helper>() << '\n';
    std::cout << "list_helper_new:  " << name<Scheme<test_type2_new>::list_helper>() << '\n';
    std::cout << "list_t:           " << name<Scheme<test_type2_bad>::list_t>() << '\n';
    std::cout << "list_new:         " << name<Scheme<test_type2_new>::list_t>() << '\n';
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

    using test_type_bad = Damaging<Living<Naming<test_struct>>>;   // duplicate of test_type_bad
    using test_type2_bad = Naming<Damaging<Living<test_struct>>>;  // duplicate of test_type2_bad
    //TODO: check differences of list_t in example
#ifdef NO_PREMADE_PROPERTIES
    static_assert(not std::is_same_v<Scheme<test_type_bad>::list_t,
                                     Scheme<test_type2_bad>::list_t>);  // !
    std::cout << "Scheme::list_t of bad types:\n";
    std::cout << name<Scheme<test_type_bad>::list_t>() << '\n';
    std::cout << name<Scheme<test_type2_bad>::list_t>() << '\n';
    std::cout << '\n';
#else
    static_assert(std::is_same_v<Scheme<test_type_bad>::list_t,
                                 Scheme<test_type2_bad>::list_t>);  // !
    std::cout << "Scheme::list_t of bad types:\n";
    std::cout << name<Scheme<test_type_bad>::list_t>() << '\n';
    std::cout << name<Scheme<test_type2_bad>::list_t>() << '\n';
    std::cout << '\n';
#endif

    using test_type_new = add_properties_ordered<test_struct, Damaging, Living, Naming>;   // duplicate of test_type_new
    using test_type2_new = add_properties_ordered<test_struct, Naming, Damaging, Living>;  // duplicate of test_type2_new

    static_assert(not std::is_same_v<test_type_bad,
                                     test_type2_bad>);  // ! incorect order
    static_assert(std::is_same_v<test_type_new,
                                 test_type2_new>);  // add_properties can handle ordering

    std::cout << "Check literals pointers of property_data::name():\n\n";

    static_assert(Naming<test_struct>::property_data::name() == Naming<test_struct_2>::property_data::name());
    std::cout << (long long*)Naming<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Naming<test_struct_2>::property_data::name() << '\n';
    std::cout << Naming<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Living<test_struct>::property_data::name() == Living<test_struct_2>::property_data::name());
    std::cout << (long long*)Living<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Living<test_struct_2>::property_data::name() << '\n';
    std::cout << Living<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Damaging<test_struct>::property_data::name() == Damaging<test_struct_2>::property_data::name());
    std::cout << (long long*)Damaging<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Damaging<test_struct_2>::property_data::name() << '\n';
    std::cout << Damaging<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Protecting<test_struct>::property_data::name() == Protecting<test_struct_2>::property_data::name());
    std::cout << (long long*)Protecting<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Protecting<test_struct_2>::property_data::name() << '\n';
    std::cout << Protecting<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Healing<test_struct>::property_data::name() == Healing<test_struct_2>::property_data::name());
    std::cout << (long long*)Healing<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Healing<test_struct_2>::property_data::name() << '\n';
    std::cout << Healing<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Restoring<test_struct>::property_data::name() == Restoring<test_struct_2>::property_data::name());
    std::cout << (long long*)Restoring<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Restoring<test_struct_2>::property_data::name() << '\n';
    std::cout << Restoring<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';
    static_assert(Wearing<test_struct>::property_data::name() == Wearing<test_struct_2>::property_data::name());
    std::cout << (long long*)Wearing<test_struct>::property_data::name() << '\n';
    std::cout << (long long*)Wearing<test_struct_2>::property_data::name() << '\n';
    std::cout << Wearing<test_struct_2>::property_data::name() << '\n';
    std::cout << '\n';

    using x_type = add_properties_ordered<test_struct, Protecting, Living>;
    std::cout << "x_type:       " << name<x_type>() << '\n';
    std::cout << "base:         " << name<Scheme<x_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<x_type>::list_helper>() << '\n';
    std::cout << "list_t:       " << name<Scheme<x_type>::list_t>() << '\n';
    std::cout << '\n';
    using y_type = add_properties_ordered<x_type, Wearing, Restoring>;
    std::cout << "y_type:       " << name<y_type>() << '\n';
    std::cout << "base:         " << name<Scheme<y_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<y_type>::list_helper>() << '\n';
    std::cout << "list_t:       " << name<Scheme<y_type>::list_t>() << '\n';
    std::cout << '\n';
    using z_type = add_properties_ordered<test_struct, Wearing, Restoring, Protecting, Living>;  // correctly ordered type
    std::cout << "z_type:       " << name<z_type>() << '\n';
    std::cout << "base:         " << name<Scheme<z_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<z_type>::list_helper>() << '\n';
    std::cout << "list_t:       " << name<Scheme<z_type>::list_t>() << '\n';
    std::cout << '\n';
    static_assert(std::same_as<y_type, z_type>);

    using b_type = add_properties_ordered<test_struct, B, Wearing, Restoring, A, A, Protecting, Living, B>;  // correctly ordered type
    std::cout << "b_type:       " << name<b_type>() << '\n';
    std::cout << "base:         " << name<Scheme<b_type>::base>() << '\n';
    std::cout << "list_helper:  " << name<Scheme<b_type>::list_helper>() << '\n';
    std::cout << "list_t:       " << name<Scheme<b_type>::list_t>() << '\n';
    std::cout << '\n';
}
