#include <boost/core/demangle.hpp>
#include <typeinfo>
#include "Examples/preety_print.hpp"
#include "basic_strategies.hpp"

template <class T>
std::string name() {
    return boost::core::demangle(typeid(T).name());
}

// is_base_of_template
template <template <typename> class base, typename derived>
struct is_base_of_template_impl {
    template <typename T>
    static constexpr std::true_type test(const base<T>*);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template <template <typename> class base, typename derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;

constexpr char a_type_name[] = "A";

template <typename T>
struct A_ : T {
    using property_data = PropertyData<A_, T, a_type_name>;
};

template <typename T>
using A = std::conditional_t<is_base_of_template<A_, T>::value, T, A_<T>>;

constexpr char b_type_name[] = "B";

template <typename T>
struct B : T {
    using property_data = PropertyData<B, T, b_type_name>;
};

struct Element_empty {};

struct Element {
    Name name{};
};

struct Element_n {
    Name name{};
    Health hp{100};
};

struct Element_Dmg : Element_n {
    Damage dmg{1};
};

static_assert(std::is_same_v<
              A<Element>,
              A<A<Element>>>);

int main() {
    std::cout << "create_ordered_property_list<A, B, Protecting, A, Protecting, Living, Damaging, A>" << '\n';
    std::cout << name<create_ordered_property_list<A, B, Protecting, A, Protecting, Living, Damaging, A>>() << '\n'
              << '\n';

    using type_00 = create_ordered_property_list<Damaging, Protecting>;
    using type_01 = create_ordered_property_list<Protecting, Damaging>;
    static_assert(std::is_same_v<
                  type_00,
                  type_01>);  // checking reorder
    std::cout << "checking reorder" << '\n';
    std::cout << name<type_00>() << '\n';
    std::cout << name<type_01>() << '\n';
    std::cout << '\n';

    using type_1 = create_ordered_property_list<Damaging, Damaging, Living, Damaging>;
    using type_2 = create_ordered_property_list<Living, Damaging>;
    static_assert(std::is_same_v<
                  type_1,
                  type_2>);  // checking removing of duplicates and reorder
    std::cout << "checking removing of duplicates and reorder" << '\n';
    std::cout << name<type_1>() << '\n';
    std::cout << name<type_2>() << '\n';
    std::cout << '\n';

    using type_3 = create_ordered_property_list<A, B, Protecting, Living, Damaging>;
    using type_4 = create_ordered_property_list<B, A, Protecting, Damaging, Living>;
    static_assert(std::is_same_v<
                  type_1,
                  type_2>);  // checking removing of unknown properties and reorder
    std::cout << "checking removing of unknown properties and reorder" << '\n';
    std::cout << name<type_3>() << '\n';
    std::cout << name<type_4>() << '\n';
    std::cout << '\n';

    using type_5 = create_ordered_property_list<A, Wearing, B, Protecting, A, Restoring, Naming, Living, Damaging, Healing, A>;
    using type_6 = create_ordered_property_list<Restoring, B, A, Living, Healing, Protecting, Protecting, Damaging, Protecting, Wearing, Living, Naming, Protecting>;
    using type_6_b = create_ordered_property_list<Restoring, A, B, Living, Healing, Protecting, Protecting, Damaging, Protecting, Wearing, Living, Naming, Protecting>;
    static_assert(not std::is_same_v<
                  type_5,
                  type_6>);  // checking all features (unorder of A and B)
    static_assert(std::is_same_v<
                  type_5,
                  type_6_b>);  // checking all features
    std::cout << "checking all features" << '\n';
    std::cout << name<type_5>() << '\n';
    std::cout << name<type_6>() << '\n';
    std::cout << name<type_6_b>() << '\n';
    std::cout << '\n';

    std::cout << name<create_ordered_property_list<>>() << " - no properties" << '\n';                   // no properties
    std::cout << name<create_ordered_property_list<A, B>>() << " - all properties are unknown" << '\n';  // all properties are unknown
    std::cout << '\n';

    std::cout << Property<A>::value << " - A priority" << '\n';
    std::cout << Property<B>::value << " - B priority" << '\n';
    std::cout << Property<Naming>::value << " - Naming priority" << '\n';
    std::cout << Property<Living>::value << " - Living priority" << '\n';
    std::cout << Property<Wearing>::value << " - Wearing priority" << '\n';
    std::cout << Property<Damaging>::value << " - Damaging priority" << '\n';
    std::cout << Property<Protecting>::value << " - Protecting priority" << '\n';
    std::cout << Property<Healing>::value << " - Healing priority" << '\n';
    std::cout << Property<Restoring>::value << " - Restoring priority" << '\n';
    std::cout << '\n';

    std::cout << "build_into_t from list:" << '\n';
    std::cout << '\n';
    std::cout << "build_into_t<Element, list<Property<Damaging>, Property<Damaging>>> - duplicates are ignored by property Damaging itself" << '\n';
    using type_7 = build_into_t<Element, list<Property<Damaging>, Property<Damaging>>>;
    using type_7b = Damaging<Element>;
    static_assert(std::is_same_v<
                  type_7,
                  type_7b>);
    std::cout << name<type_7>() << '\n';
    std::cout << name<type_7b>() << '\n';
    std::cout << '\n';
    std::cout << "build_into_t<Element, list<Property<A>, Property<A>>> - unknown types (not listed in order_list) are ignored by PropertyOrder" << '\n';
    using type_7c = build_into_t<Element, list<Property<A>, Property<A>>>;
    using type_7d = A<Element>;
    static_assert(std::is_same_v<
                  type_7c,
                  type_7d>);
    std::cout << name<type_7c>() << '\n';
    std::cout << name<type_7d>() << '\n';
    std::cout << '\n';
    std::cout << "build_into_t<Element, list<Property<Damaging>, Property<Living>>> - order priority is not checked in build_into_t" << '\n';
    using type_8 = build_into_t<Element, list<Property<Damaging>, Property<Living>>>;
    using type_8b = Damaging<Living<Element>>;
    static_assert(std::is_same_v<
                  type_8,
                  type_8b>);
    std::cout << name<type_8>() << '\n';
    std::cout << name<type_8b>() << '\n';
    std::cout << '\n';
    std::cout << "build_into_t<Element, list<Property<Living>, Property<Damaging>>>" << '\n';
    using type_9 = build_into_t<Element, list<Property<Living>, Property<Damaging>>>;
    using type_9b = Living<Damaging<Element>>;
    static_assert(std::is_same_v<
                  type_9,
                  type_9b>);
    std::cout << name<type_9>() << '\n';
    std::cout << name<type_9b>() << '\n';
    std::cout << '\n';

    using type_A = add_properties<Element, Damaging, Living, Damaging, Damaging, Living, Damaging>;  // known properties are: Damaging, Living, Protecting; It's because they are in order_list
    using type_B = Living<Damaging<Element>>;
    static_assert(std::is_same_v<
                  type_A,
                  type_B>);

    using type_C = add_properties<Element, Damaging, Living, Damaging, Damaging, Living>;
    static_assert(std::is_same_v<
                  type_C,
                  Living<Damaging<Element>>>);

    using type_D = add_properties<Element, Damaging, Damaging, Living, Damaging, Damaging, Damaging>;
    static_assert(std::is_same_v<
                  type_D,
                  Living<Damaging<Element>>>);

    using type_E = add_properties<Element, Damaging, Damaging, Living, Damaging, Damaging>;
    static_assert(std::is_same_v<
                  type_E,
                  Living<Damaging<Element>>>);

    using type_F = add_properties<Element, Living, Damaging>;
    static_assert(std::is_same_v<
                  type_F,
                  Living<Damaging<Element>>>);

    std::cout << "use add_properties:" << '\n';
    std::cout << '\n';

    using type_t4 = add_properties<Element_n, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    std::cout << "add_properties<Element_n, Protecting, Damaging, Living, Protecting, Damaging, Living> - will remove duplication and order properties" << '\n';
    std::cout << "result type:   " << name<type_t4>() << '\n';
    auto t4 = type_t4{
        Name{"Element 4"},
        Damage{50},
        std::tuple{15, BodyLocation::Arms},
        Health{50}};
    print_object(Object{t4});

    using type_t5 = add_properties<Element_n, Living, Damaging, Protecting, Protecting, Living, Damaging>;
    std::cout << "add_properties<Element_n, Living, Damaging, Protecting, Protecting, Living, Damaging> - will remove duplication and order properties" << '\n';
    std::cout << "result type:   " << name<type_t5>() << '\n';
    [[maybe_unused]] auto t5 = type_t5{
        Name{"Element 5"},
        Damage{50},
        std::tuple{15, BodyLocation::Arms},
        Health{50}};
    print_object(Object{t5});

    [[maybe_unused]] auto t6_0 = Element_Dmg{
        Name{"Element 6"},
        Health{50},
        Damage{50}};

    using type_t6 = add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    std::cout << "add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living> - will remove duplication, ignore Damaging/Living, and order properties" << '\n';
    std::cout << "result type:   " << name<type_t6>() << '\n';
    static_assert(std::is_same_v<
                  type_t6,
                  Protecting<Element_Dmg>>);
    [[maybe_unused]] auto t6 = type_t6{
        Name{"Element 6"},
        std::tuple{15, BodyLocation::Arms},
        Health{50},
        Damage{50}};  // will remove duplication, inverited Damaging, and order properties
    print_object(Object{t6});

    static_assert(sizeof(t4) == sizeof(t5));
    static_assert(sizeof(t5) == sizeof(t6));

    using type_t9 = add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    [[maybe_unused]] auto t9 = type_t9{
        Name{"Element 9"},
        std::ignore};
    std::cout << name<decltype(t9)>() << '\n';
    print_object(Object{t9});

    using type_t10 = add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    [[maybe_unused]] auto t10 = type_t10{};
    std::cout << name<decltype(t10)>() << '\n';
    print_object(Object{t10});

    using x_type = add_properties<Element, Protecting, Living>;
    std::cout << "x_type:   " << name<x_type>() << '\n';
    using y_type = add_properties<x_type, Wearing, Restoring>;
    std::cout << "y_type:   " << name<y_type>() << '\n';
    using z_type = add_properties<Element, Wearing, Restoring, Protecting, Living>;
    std::cout << "z_type:   " << name<z_type>() << '\n';
    std::cout << '\n';

    auto fill_and_print_type = [](auto& el) {
        traits::accessHealth::get(el) = Health{500};
        traits::accessArmorWear::get(el) = {};
        traits::accessProtection::get(el) = Protection{15, BodyLocation::Arms};
        traits::accessRestoreEffects::get(el) = {EffectType::Burn};
        print_object(Object{el});
    };

    y_type Y{};
    traits::accessName::get(Y) = Name{"y_type Y"};
    fill_and_print_type(Y);

    z_type Z{};
    traits::accessName::get(Z) = Name{"z_type Z"};
    fill_and_print_type(Z);

    static_assert(sizeof(Y) == sizeof(Z));

    static_assert(std::is_same_v<
                  y_type,
                  z_type>);

    using a_type = Damaging<Living<Naming<Element>>>;                  // ! incorrect order
    using b_type = add_properties<a_type>;                             // add_properties should fix incorrect type
    using c_type = add_properties<Element, Damaging, Living, Naming>;  // correct order
    using d_type = add_properties<Damaging<Element>, Naming, Living>;  // correct order

    using e_type =
        B<Protecting<A<Damaging<A<B<Element_empty>>>>>>;
    using e_type_2 =
        add_properties<B<Protecting<A<Damaging<A<B<Element_empty>>>>>>>;
    using f_type = add_properties<
        B<Protecting<A<Damaging<A<B<Element_empty>>>>>>,
        Naming, Living>;  // ? Should A and B types that are not close to base_type be removed by ordering function
    std::cout << "e_type:       " << name<e_type>() << '\n';
    std::cout << "e_type fix:   " << name<e_type_2>() << '\n';
    std::cout << "f_type:       " << name<f_type>() << " = e_type + Naming + Living" << '\n';

    static_assert(std::is_same_v<
                  b_type,
                  c_type>);
    static_assert(std::is_same_v<
                  c_type,
                  d_type>);
}
