#include "../../basic_strategies.hpp"
#include "../../demangle_type_name.hpp"
#include "Examples/preety_print.hpp"

struct Empty {};

struct Element_name {
    Name name{};
};

struct Element_name_hp {
    Name name{};
    Health hp{100};
};

struct Element_name_hp_dmg : Element_name_hp {
    Damage dmg{1};
};

struct Element_hp_name {
    Element_hp_name(const Name& name, const Health& hp)  // name must always be the first argument
        : hp{hp}, name{name} {}

    Health hp{100};
    Name name{};
};

using type_A = Living<Damaging<Element_name>>;
using type_B = add_properties<Element_name, Damaging, Living, Damaging, Damaging, Living, Damaging>;
using type_C = add_properties<Element_name, Damaging, Living, Damaging, Damaging, Living>;
using type_D = add_properties<Element_name, Damaging, Damaging, Living, Damaging, Damaging, Damaging>;
using type_E = add_properties<Element_name, Damaging, Damaging, Living, Damaging, Damaging>;
using type_F = add_properties<Element_name, Living, Damaging>;

// checks that show reordering and removing of duplicated Properties
static_assert(std::is_same_v<type_B, type_A>);
static_assert(std::is_same_v<type_C, type_A>);
static_assert(std::is_same_v<type_D, type_A>);
static_assert(std::is_same_v<type_E, type_A>);
static_assert(std::is_same_v<type_F, type_A>);

const auto default_name = Name{"Element"};
const auto default_health = Health{50};
const auto default_damage = Damage{50};
const auto default_protection = Protection{15, BodyLocation::Arms};

int main() {
    std::cout << "'add_properties' example:" << '\n'
              << '\n';

    std::cout << "1) add_properties<Empty, Naming, Protecting, Damaging, Living, Protecting, Damaging, Living> - will remove duplication and order properties" << '\n'
              << '\n';

    using type_1 = add_properties<Empty, Naming, Damaging, Living, Protecting, Damaging, Living>;
    using type_2 = add_properties<Element_name, Naming, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    using type_3 = add_properties<Element_name_hp, Naming, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    using type_4 = add_properties<Element_name_hp_dmg, Naming, Protecting, Damaging, Living, Protecting, Damaging, Living>;
    using type_5 = add_properties<Element_hp_name, Naming, Protecting, Damaging, Living, Protecting, Damaging, Living>;

    auto create_type = []<typename T>(T) {
        auto type = T{
            default_name,
            default_health,
            default_damage,
            default_protection};
        std::cout << "result type:   " << name<T>() << '\n';
        print_object(Object{type});
    };

    create_type(type_1{});
    create_type(type_2{});

    auto type3 = type_3{
        default_name,        // own name as first argument
        default_damage,      //
        default_protection,  //
        default_health,      // own hp moved at end
    };
    std::cout << "result type:   " << name<type_3>() << '\n';
    print_object(Object{type3});

    auto type4 = type_4{
        default_name,        // own name as first argument
        default_protection,  //
        default_health,      // own hp moved at end
        default_damage,      // own dmg moved
    };
    std::cout << "result type:   " << name<type_4>() << '\n';
    print_object(Object{type4});

    auto type5 = type_5{
        default_name,        // own name as first argument
        default_damage,      //
        default_protection,  //
        default_health,      // own hp moved at end
    };
    std::cout << "result type:   " << name<type_5>() << '\n';
    print_object(Object{type5});

    return 0;
}
