#define IGNORE_ORDER_LIST

#include "Base.hpp"
#include "With.hpp"
#include "default_values.hpp"

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

int main() {
    std::cout << '\n';

    // MARK: print lambda

    auto print = [](auto type) {
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "x      = " << type.x << '\n';
        std::cout << "y      = " << type.y << '\n';
        std::cout << "int    = " << trait<int>::get(type) << '\n';
        std::cout << "float  = " << trait<float>::get(type) << '\n';
        std::cout << "double = " << trait<double>::get(type) << '\n';
        std::cout << '\n';
    };

    // MARK: update lambda

    // update rest of target parameters
    auto update = [](auto& target) {
        using boost::mp11::mp_unique;
        using std::remove_cvref_t;
        using std::same_as;

        return [&target]<typename... Args>
            requires(
                (same_as<mp_unique<list<remove_cvref_t<Args>...>>, list<remove_cvref_t<Args>...>>) and         // every argument have unique type
                (trait<remove_cvref_t<Args>>::template accessable<remove_cvref_t<decltype(target)>> and ...))  // every type is accessable by trait
        (Args&&... args) {
            ((trait<remove_cvref_t<Args>>::get(target) = std::forward<Args>(args)), ...);
        };
    };

    // MARK: modify target
    auto tlist = With::Name | With::Health | With::Protection | With::Damage;

    Base base{default_x, default_y};  // target

    auto type3 = Base{default_x, default_y} | tlist;
    auto type4 = base | tlist;                                                          // modify existing target type
    auto type5 = base | (With::Name | With::Health | With::Protection | With::Damage);  // modify existing target type

    static_assert(std::same_as<
                  decltype(type4),
                  decltype(type5)>);

    update(type3)(
        Health{100, 100},
        float{3.14f},   // type<float>
        default_int,    // type<int>
        double{20.20},  // type<double>
        Damage{5, DamageType::Magical},
        Protection{10, BodyLocation::Head},
        Name{"Test"});

    update(type4)(
        default_int,
        default_float,
        default_double,
        default_health,
        default_damage,
        default_protection,
        default_name);

    update(type5)(
        Name{"Test 5"},
        // default_int,
        // default_float,
        default_double);

    print(type3);
    print(type4);
    print(type5);
}
