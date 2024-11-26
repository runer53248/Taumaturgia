#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"

struct Empty {};

struct Element_name {
    Name name{};
};

struct Element_name_hp {
    Name name{};
    Health hp{};
};

struct Element_name_hp_dmg : public Element_name_hp {
    Damage dmg{};
};

struct Element_hp_name {
    Element_hp_name() = delete;                          // by defalt deleted anyway - just show the point
    Element_hp_name(const Name& name, const Health& hp)  // name must always be the first argument
        : hp{hp}, name{name} {}

    Health hp{};
    Name name{};
};

const auto default_name = Name{"Element"};
const auto default_health = Health{50};
const auto default_damage = Damage{50};
const auto default_protection = Protection{15, BodyLocation::Arms};

template <auto F, typename... T, typename... Args>
auto templated_call(Args&&... args) {
    return F.template operator()<T...>(std::forward<Args>(args)...);
}

int main() {
    std::cout << "add_properties example1" << '\n'
              << '\n';

    std::cout << "p_list::add_properties (and add_properties) removes duplications and orders properties" << '\n'
              << '\n';

    std::cout << "p_list = properties_list<Naming, Damaging, Living, Protecting, Damaging, Living>" << '\n'
              << '\n';
    using p_list = properties_list<Naming, Damaging, Living, Protecting, Damaging, Living>;

    using base_1 = Empty;
    using base_2 = Element_name;
    using base_3 = Element_name_hp;
    using base_4 = Element_name_hp_dmg;
    using base_5 = Element_hp_name;
    using base_6 = add_properties_ordered<Element_name, Damaging>;

    auto create_type = []<typename T>() {
        return p_list::apply_ordered_properties_to<T>{
            default_name,
            default_health,
            default_damage,
            default_protection};
    };

    auto print_type = []<typename BASE, typename TYPE>(TYPE&& tp) {
        std::cout << "base type:   " << name<BASE>() << '\n';
        std::cout << "result type: " << name<TYPE>() << '\n';
        print_object(Object{tp});
    };

    auto type1 = templated_call<create_type, base_1>();
    templated_call<print_type, base_1>(type1);

    auto type2 = templated_call<create_type, base_2>();
    templated_call<print_type, base_2>(type2);

    auto type3 = p_list::apply_ordered_properties_to<base_3>{
        default_name,        // own name as first argument
        default_damage,      //
        default_protection,  //
        default_health       // own hp moved at end of c-tor
    };
    templated_call<print_type, base_3>(type3);

    auto type4 = p_list::apply_ordered_properties_to<base_4>{
        default_name,        // own name as first argument
        default_protection,  //
        default_health,      // own hp moved at end of c-tor - order depends on base struct c-tor order now
        default_damage       // own dmg moved at end
    };
    templated_call<print_type, base_4>(type4);

    auto type5 = p_list::apply_ordered_properties_to<base_5>{
        default_name,        // own name as first argument
        default_damage,      //
        default_protection,  //
        default_health       // own hp moved at end of c-tor
    };
    templated_call<print_type, base_5>(type5);

    auto type6 = templated_call<create_type, base_6>();  // all properties but name given by add_properties feature - correct order in c-tor
    templated_call<print_type, base_6>(type6);

    auto fill_type = [](auto&& type) {
        trait<Name>::get(type) = default_name;
        trait<Health>::get(type) = default_health;
        trait<Damage>::get(type) = default_damage;
        trait<Protection>::get(type) = default_protection;
    };

    fill_type(type1);
    fill_type(type2);
    fill_type(type3);
    fill_type(type4);
    fill_type(type5);
    fill_type(type6);

    static_assert(std::is_same_v<decltype(type1), Living<Damaging<Protecting<Naming<base_1>>>>>);
    static_assert(std::is_same_v<decltype(type1), add_properties_ordered<base_1, Naming, Living, Damaging, Protecting>>);
    static_assert(std::is_same_v<decltype(type2), Living<Damaging<Protecting<base_2>>>>);
    static_assert(std::is_same_v<decltype(type2), add_properties_ordered<base_2, Living, Damaging, Protecting>>);
    static_assert(std::is_same_v<decltype(type3), Damaging<Protecting<base_3>>>);
    static_assert(std::is_same_v<decltype(type3), add_properties_ordered<base_3, Damaging, Protecting>>);
    static_assert(std::is_same_v<decltype(type4), Protecting<base_4>>);
    static_assert(std::is_same_v<decltype(type4), add_properties_ordered<base_4, Protecting>>);
    static_assert(std::is_same_v<decltype(type5), Damaging<Protecting<base_5>>>);
    static_assert(std::is_same_v<decltype(type5), add_properties_ordered<base_5, Damaging, Protecting>>);
    static_assert(std::is_same_v<decltype(type6), Living<Damaging<Protecting<Element_name>>>>);
    static_assert(std::is_same_v<decltype(type6), add_properties_ordered<base_6, Living, Protecting>>);

    static_assert(sizeof(type1) == sizeof(type2));
    static_assert(sizeof(type1) == sizeof(type3));
    static_assert(sizeof(type1) == sizeof(type4));
    static_assert(sizeof(type1) == sizeof(type5));
    static_assert(sizeof(type1) == sizeof(type6));

    return 0;
}

using type_A = Living<Damaging<Element_name>>;
using type_B = add_properties_ordered<Element_name, Damaging, Living, Damaging, Damaging, Living, Damaging>;
using type_C = add_properties_ordered<Element_name, Damaging, Living, Damaging, Damaging, Living>;
using type_D = add_properties_ordered<Element_name, Damaging, Damaging, Living, Damaging, Damaging, Damaging>;
using type_E = add_properties_ordered<Element_name, Damaging, Living, Damaging>;
using type_F = add_properties_ordered<Element_name, Living, Damaging, Living>;

// checks that show reordering and removing of duplicated Properties
static_assert(std::is_same_v<type_B, type_A>);
static_assert(std::is_same_v<type_C, type_A>);
static_assert(std::is_same_v<type_D, type_A>);
static_assert(std::is_same_v<type_E, type_A>);
static_assert(std::is_same_v<type_F, type_A>);
