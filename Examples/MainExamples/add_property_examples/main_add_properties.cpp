#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"
#include "Examples/PreetyPrint/preety_print.hpp"

struct Empty {};

struct Element_name {
    Name name{};
};

struct Element_name_hp {
    Name name{};
    Health hp{100};
};

struct Element_name_hp_dmg : public Element_name_hp {
    Damage dmg{1};
};

static_assert(std::is_same_v<
              A<Element_name>,
              A<A<Element_name>>>);

int main() {
    std::cout << "D. 'add_properties' examples:" << '\n'
              << '\n';

    using type_1 = add_properties<Element_name_hp_dmg, Protecting, Damaging, Living>;

    auto type1 = type_1{Name{"Element 9"}, std::ignore};
    std::cout << name<decltype(type1)>() << '\n';
    print_object(Object{type1});

    auto type2 = type_1{};
    std::cout << name<decltype(type2)>() << '\n';
    print_object(Object{type2});

    using base_type = add_properties<Element_name, Protecting, Living>;
    using y_type = add_properties<base_type, Wearing, Restoring>;
    using z_type = add_properties<Element_name, Wearing, Restoring, Protecting, Living>;
    static_assert(std::is_same_v<y_type, z_type>);
    std::cout << "base_type:  " << name<base_type>() << '\n';
    std::cout << "y_type:     " << name<y_type>() << '\n';
    std::cout << "z_type:     " << name<z_type>() << '\n';
    std::cout << '\n';

    auto fill_and_print_type = [](auto& el) {
        Livingable_trait::get(el) = Health{500};
        Wearingable_trait::get(el) = {};
        Protectingable_trait::get(el) = Protection{15, BodyLocation::Arms};
        Restoringable_trait::get(el) = {EffectType::Burn};
        print_object(Object{el});
    };

    y_type Y{};
    Namingable_trait::get(Y) = Name{"y_type Y"};
    fill_and_print_type(Y);

    z_type Z{};
    Namingable_trait::get(Z) = Name{"z_type Z"};
    fill_and_print_type(Z);

    static_assert(sizeof(Y) == sizeof(Z));

    using type_wrong_order = Damaging<Living<Naming<Element_name>>>;        // ! incorrect order
    using type_fix = add_properties<type_wrong_order>;                      // add_properties will fix incorrect type
    using c_type = add_properties<Element_name, Damaging, Living, Naming>;  // correct order
    using d_type = add_properties<Damaging<Element_name>, Naming, Living>;  // correct order

    static_assert(not std::is_same_v<
                  type_wrong_order,
                  type_fix>);

    static_assert(std::is_same_v<
                  type_fix,
                  c_type>);
    static_assert(std::is_same_v<
                  c_type,
                  d_type>);

    using e_type = B<Protecting<A<Damaging<A<B<Empty>>>>>>;
    using e_type_fix = add_properties<e_type>;
    using f_type = add_properties<e_type, Naming, Living>;
    std::cout << "e_type:       " << name<e_type>() << '\n';
    std::cout << "e_type fix:   " << name<e_type_fix>() << '\n';
    std::cout << "f_type:       " << name<f_type>() << " = e_type + Naming + Living" << '\n';

    return 0;
}
