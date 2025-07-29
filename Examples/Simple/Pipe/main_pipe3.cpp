#define IGNORE_ORDER_LIST

#include "../Base.hpp"
#include "Usage/With.hpp"
#include "default_values.hpp"
#include "print.hpp"
#include "update.hpp"

int main() {
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
        if constexpr (trait_accessable<decltype(type), std::string>) {
            std::cout << "string = " << trait<std::string>::get(type) << '\n';
        }
        std::cout << '\n';
    };

    // MARK: modify target
    auto tlist = With::Name | With::Health | With::Protection | With::Damage;

    Base base{default_x, default_y};  // target

    auto type3 = Base{default_x, default_y} | tlist;
    auto type4 = base | tlist;                                                          // modify existing target type
    auto type5 = base | (With::Name | With::Health | With::Protection | With::Damage);  // modify existing target type

    static_assert(std::same_as<
                  decltype(type3),
                  decltype(type5)>);
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

    auto typex =
        base                                //
        | With::Name                        //
        | With::Health                      //
        | With::Protection                  //
        | With::user_property<std::string>  //
        | With::Damage                      //
        | Create                            //
        ;
    auto typey =
        Base{500, 100}                      //
        | With::Name                        //
        | With::Damage                      //
        | With::user_property<std::string>  //
        | With::Protection                  //
        | With::Health                      //
        | Create                            //
        ;
    typex.getType<std::string>() = "test x";
    typey.getType<std::string>() = "test y";
    print(typex);
    print(typey);

    struct Test {
        int x;
        int y;
        Protection protection{};
        CureHealth cureHealth{};

        Test(int x, int y)
            : x{x}, y{y} {
            std::cout << "(int, int)\n";
        }
        Test(const Test&) {
            std::cout << "(const&)\n";
        }
        Test(Test&&) {
            std::cout << "op(&&)\n";
        }
        Test& operator=(const Test&) {
            std::cout << "op=(const&)\n";
            return *this;
        }
        Test& operator=(Test&&) {
            std::cout << "op=(&&)\n";
            return *this;
        }
    };

    Test test{50, 10};
    auto typez =
        test                //
        | With::Damage      //
        | With::Health      //
        | With::Health      //
        | With::Protection  //
        ;
    std::cout << "type z      = " << name<decltype(typez)>() << '\n';
    std::cout << "type z      = " << name<decltype(std::move(typez) | Create)>() << '\n';

    auto typeq1 =
        test                         //
        | WithUnordered::Damage      //
        | WithUnordered::Health      //
        | WithUnordered::Health      //
        | WithUnordered::Protection  //
        ;
    std::cout << "type q1     = " << name<decltype(typeq1)>() << '\n';
    std::cout << "type q1     = " << name<decltype(std::move(typeq1) | Create)>() << '\n';
    std::cout << "type q1     = " << name<decltype(typeq1 | Create)>() << '\n';
    static_assert(std::is_same_v<
                  decltype(std::move(typeq1) | Create),
                  decltype(typeq1 | Create)>);
    auto typeq2 =                    // * moved
        Test{500, 100}               //
        | WithUnordered::Protection  // skip
        | WithUnordered::Damage      // * moved
        | WithUnordered::Health      // * moved
        | WithUnordered::CureHealth  // skip
        | WithUnordered::Health      // skip
        ;
    std::cout << "type q2     = " << name<decltype(typeq2)>() << '\n';
    std::cout << "type q2     = " << name<decltype(std::move(typeq2) | Create)>() << '\n';
    std::cout << "type q2     = " << name<decltype(typeq2 | Create)>() << '\n';
    static_assert(std::is_same_v<
                  std::remove_reference_t<decltype(std::move(typeq2) | Create)>,
                  std::remove_reference_t<decltype(typeq2 | Create)>>);

    {
        impl::DataAndPropertiesList typeq3 =  // * moved
            Test{500, 100}                    //
            | With::Damage                    // * moved
            | WithUnordered::Health           // * moved
            ;
        std::cout << "type q3     = " << name<decltype(typeq3)>() << '\n';

        // auto type = typeq3 | Create; // ! Create required properties from same order group
        // ? add "CreateOnOrder" for ordered and "CreateUnorder" for other ones
        // ? or add implement adding properties in steps when mixed types occurs

        // std::cout << "type q3     = " << name<decltype(std::move(typeq3) | Create)>() << '\n';
        // std::cout << "type q3     = " << name<decltype(typeq3 | Create)>() << '\n';
    }

    auto typew_list = With::Damage | With::Damage | With::Health | With::Health;

    auto typew1 =       // moved once
        Test{500, 100}  //
        | typew_list;   // ! impl::pipe_helper depends on IGNORE_ORDER_LIST
    std::cout << "type w1 list = " << name<decltype(typew_list)>() << '\n';
    std::cout << "type w1      = " << name<decltype(typew1)>() << '\n';

    auto typew2 =                                                                                           // moved once
        Test{500, 100}                                                                                      //
        | (WithUnordered::Damage | WithUnordered::Damage | WithUnordered::Health | WithUnordered::Health);  // ! impl::pipe_helper depends on IGNORE_ORDER_LIST
    std::cout << "type w2 list = " << name<decltype((WithUnordered::Damage | WithUnordered::Damage | WithUnordered::Health | WithUnordered::Health))>() << '\n';
    std::cout << "type w2      = " << name<decltype(typew2)>() << '\n';
}
