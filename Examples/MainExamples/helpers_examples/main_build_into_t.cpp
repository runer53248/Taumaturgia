#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"

struct Element {
    Name name{};
};

struct Element_n {
    Name name{};
    Health hp{100};
};

struct Element_Dmg : public Element_n {
    Damage dmg{1};
};

static_assert(std::is_same_v<
              A<Element>,
              A<A<Element>>>);

using helpers::build_into_t;

int main() {
    std::cout << "C. 'build_into_t' from list examples:" << '\n'
              << '\n';

    std::cout << "1) build_into_t<Element, list<Property<Damaging>, Property<Damaging>>> - duplicates are ignored by property Damaging itself" << '\n';
    using type_7 = build_into_t<Element, list<Property<Damaging>, Property<Damaging>>>;
    using type_7b = Damaging<Element>;
    static_assert(std::is_same_v<type_7, type_7b>);
    std::cout << name<type_7>() << '\n';
    std::cout << name<type_7b>() << '\n';
    std::cout << '\n';

    std::cout << "2) build_into_t<Element, list<Property<A>, Property<A>>> - unknown types (not listed in order_list) are ignored by PropertyOrder" << '\n';
    using type_7c = build_into_t<Element, list<Property<A>, Property<A>>>;
    using type_7d = A<Element>;
    static_assert(std::is_same_v<type_7c, type_7d>);
    std::cout << name<type_7c>() << '\n';
    std::cout << name<type_7d>() << '\n';
    std::cout << '\n';

    std::cout << "3) build_into_t<Element, list<Property<Damaging>, Property<Living>>> - order priority is not checked in build_into_t" << '\n';
    using type_8 = build_into_t<Element, list<Property<Damaging>, Property<Living>>>;
    using type_8b = Damaging<Living<Element>>;
    static_assert(std::is_same_v<type_8, type_8b>);
    std::cout << name<type_8>() << '\n';
    std::cout << name<type_8b>() << '\n';
    std::cout << '\n';

    std::cout << "4) build_into_t<Element, list<Property<Living>, Property<Damaging>>>" << '\n';
    using type_9 = build_into_t<Element, list<Property<Living>, Property<Damaging>>>;
    using type_9b = Living<Damaging<Element>>;
    static_assert(std::is_same_v<type_9, type_9b>);
    std::cout << name<type_9>() << '\n';
    std::cout << name<type_9b>() << '\n';
    std::cout << '\n';

    return 0;
}
