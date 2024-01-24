#include "Examples/preety_print.hpp"
#include "basic_strategies.hpp"
#include "demangle_type_name.hpp"
#include "is_base_of_template.hpp"
#include "property_A.hpp"
#include "property_B.hpp"

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
    std::cout << "D. 'add_properties' examples:" << '\n'
              << '\n';

    using type_A = Living<Damaging<Element>>;
    using type_B = add_properties<Element, Damaging, Living, Damaging, Damaging, Living, Damaging>;
    using type_C = add_properties<Element, Damaging, Living, Damaging, Damaging, Living>;
    using type_D = add_properties<Element, Damaging, Damaging, Living, Damaging, Damaging, Damaging>;
    using type_E = add_properties<Element, Damaging, Damaging, Living, Damaging, Damaging>;
    using type_F = add_properties<Element, Living, Damaging>;
    static_assert(std::is_same_v<type_B, type_A>);
    static_assert(std::is_same_v<type_C, type_A>);
    static_assert(std::is_same_v<type_D, type_A>);
    static_assert(std::is_same_v<type_E, type_A>);
    static_assert(std::is_same_v<type_F, type_A>);

    using type_t4 = add_properties<Element_n, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    std::cout << "1) add_properties<Element_n, Protecting, Damaging, Living, Protecting, Damaging, Living> - will remove duplication and order properties" << '\n';
    std::cout << "result type:   " << name<type_t4>() << '\n';
    auto t4 = type_t4{
        Name{"Element 4"},
        Damage{50},                          // *
        std::tuple{15, BodyLocation::Arms},  // *
        Health{50}};                         // *
    print_object(Object{t4});

    using type_t5 = add_properties<Element_n, Living, Damaging, Protecting, Protecting, Living, Damaging>;
    std::cout << "2) add_properties<Element_n, Living, Damaging, Protecting, Protecting, Living, Damaging> - will remove duplication and order properties" << '\n';
    std::cout << "result type:   " << name<type_t5>() << '\n';
    static_assert(std::is_same_v<type_t5, Damaging<Protecting<Element_n>>>);
    auto t5 = type_t5{
        Name{"Element 5"},
        Damage{50},                          // !
        std::tuple{15, BodyLocation::Arms},  // !
        Health{50}};                         // !
    print_object(Object{t5});

    using type_t6 = add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    std::cout << "3) add_properties<Element_Dmg, Protecting, Damaging, Living, Protecting, Damaging, Living> - will remove duplication, ignore Damaging/Living, and order properties" << '\n';
    std::cout << "result type:   " << name<type_t6>() << '\n';
    static_assert(std::is_same_v<type_t6, Protecting<Element_Dmg>>);
    auto t6 = type_t6{
        Name{"Element 6"},
        std::tuple{15, BodyLocation::Arms},  // !
        Health{50},                          // !
        Damage{50}};                         // !
    print_object(Object{t6});

    static_assert(sizeof(t4) == sizeof(t5));
    static_assert(sizeof(t5) == sizeof(t6));

    auto t9 = type_t6{Name{"Element 9"}, std::ignore};
    std::cout << name<decltype(t9)>() << '\n';
    print_object(Object{t9});

    auto t10 = type_t6{};
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

    static_assert(std::is_same_v<
                  b_type,
                  c_type>);
    static_assert(std::is_same_v<
                  c_type,
                  d_type>);

    using e_type = B<Protecting<A<Damaging<A<B<Element_empty>>>>>>;
    using e_type_2 = add_properties<e_type>;
    using f_type = add_properties<e_type, Naming, Living>;  // ? Should A and B types that are not close to base_type be removed by ordering function?
    std::cout << "e_type:       " << name<e_type>() << '\n';
    std::cout << "e_type fix:   " << name<e_type_2>() << '\n';
    std::cout << "f_type:       " << name<f_type>() << " = e_type + Naming + Living" << '\n';

    return 0;
}
