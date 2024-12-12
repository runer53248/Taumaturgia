#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Introduction/order_list/order_list.hpp"

#include <iostream>
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/demangle_type_name.hpp"
#include "Usage/With.hpp"

struct Base {};

struct AccessInt {
    template <size_t S>
    static constexpr decltype(auto) get(auto& el) {
        return (el.template getType<int, S>());
    }
};

int main() {
    auto type =
        Base{}  //
        // | With::user_property<int, struct second_int>          // ! check ignored - added with correct order
        | Property<i_p2::type>{}   // ! check ignored - added with correct order
        | Property<i_p2::order>{}  // ignored
        | Property<i_p3::order>{}  // ! only higher order index will be used
        | Property<i_p1::order>{}  // ignored
        // | With::user_property<int, struct second_int>          // ? will not work if order version of <int, second_int> called before
        | Property<f_p_t>{}                                    //
        | Property<s_p2::type>{}                               // both added  with correct order
        | Property<s_p1::type>{}                               // both added with correct order
        | With::user_property_order<bool, struct first_bool>   //
        | With::user_property_order<bool, struct second_bool>  // ! only last of unordered will be used
        | With::user_property<char, struct first_char>         // both char added
        | With::user_property<char, struct second_char>        // both char added
        | With::user_property<float>                           //
        | Property<s_p1::type>{}                               // ! duplicates ignored as always
        | Property<i_p3::order>{}                              // ! duplicates ignored as always
        | With::Damage                                         //
        | Create;

    AccessInt::get<0>(type) = 100;
    AccessInt::get<1>(type) = 200;
    AccessInt::get<2>(type) = 300;  // same as above - get<1> == 300
    std::cout << type.getType<int, 0>() << '\n';
    std::cout << type.getType<int, 1>() << '\n';
    std::cout << type.getType<int, 2>() << '\n';  // same as type.getType<int, 1>
    std::cout << '\n';

    using Type = decltype(type);
    Type type2{5, 15, 3.2f, "text", "title", true, 'a', 'b', Damage{100}};

    auto parse_type_name = [](std::string text) {
        std::string what = "impl::UserProperty_<";
        size_t counter = 0;
        std::string into = "\n";
        for (
            auto target = text.find(", " + what);
            target != std::string::npos;
            target = text.find(", " + what)) {
            text.replace(target, what.size() + 2, " : " + std::to_string(counter++) + into);
        }
        for (
            auto target = text.find(what);
            target != std::string::npos;
            target = text.find(what)) {
            text.replace(target, what.size(), into);
        }

        what = name<std::string>();
        into = "std::string";
        for (
            auto target = text.find(what);
            target != std::string::npos;
            target = text.find(what)) {
            text.replace(target, what.size(), into);
        }

        size_t after_base = std::string::npos;
        if (auto target = text.find(", Base>,"); target != std::string::npos) {
            text.replace(target, 8, " : " + std::to_string(counter++) + "\n-> Base\n");
            after_base = target;
        }
        if (auto target = text.find(", Base, "); target != std::string::npos) {
            text.replace(target, 8, " : " + std::to_string(counter++) + "\n-> Base\n");
            after_base = target;
        }

        if (after_base != std::string::npos) {
            text.insert(after_base + 13, "Tokens: ");
        }
        what = ">";
        into = "";
        for (
            auto target = text.find(what, after_base + 13);
            target != std::string::npos;
            target = text.find(what, after_base + 13)) {
            text.replace(target, what.size(), into);
        }

        text += '\n';
        return text;
    };

    std::cout << "decltype(type) " << parse_type_name(name<decltype(type2)>()) << '\n';
    std::cout << "int         " << type2.getType<int, 0>() << '\n';
    std::cout << "int         " << type2.getType<int, 1>() << '\n';
    std::cout << "float       " << type2.getType<float>() << '\n';
    std::cout << "std::string " << type2.getType<std::string, 0>() << '\n';
    std::cout << "std::string " << type2.getType<std::string, 1>() << '\n';
    std::cout << "bool        " << type2.getType<bool>() << '\n';
    std::cout << "char        " << type2.getType<char, 0>() << '\n';
    std::cout << "char        " << type2.getType<char, 1>() << '\n';
    // std::cout << type2.getType<Damage>() << '\n';
    // std::cout << type2.getDamage() << '\n';
    std::cout << "Damage      " << trait<Damage>::get(type2) << '\n';
    std::cout << '\n';

    std::cout << "Type1 " << parse_type_name(name<decltype(type)>()) << '\n';
    std::cout << '\n';

    using Type2 = add_properties_ordered<Base, i_p2::type, i_p3::type, f_p::type, i_p1::type>;
    using Type3 = add_properties_ordered<Base, f_p_t, i_p3_t, i_p2_t>;

    static_assert(helpers::impl::same_priority<
                      Property<i_p2_t>,
                      Property<i_p3_t>>::value == false);

    std::cout << "Type2 " << parse_type_name(name<Type2>()) << '\n';
    std::cout << "Type3 " << parse_type_name(name<Type3>()) << '\n';
    std::cout << '\n';

    std::cout << "add_properties_ordered<Base, i_p2_t, i_p3_t> " << parse_type_name(name<add_properties_ordered<Base, i_p2_t, i_p3_t>>())
              << '\n';

    std::cout << Property<i_p1::type>::value << '\n';
    std::cout << Property<i_p2::type>::value << '\n';
    std::cout << Property<i_p3::type>::value << '\n';
    std::cout << Property<f_p::type>::value << '\n';
    std::cout << '\n';
    std::cout << Property<i_p1::order>::value << '\n';
    std::cout << Property<i_p2::order>::value << '\n';
    std::cout << Property<i_p3::order>::value << '\n';
    std::cout << '\n';

    Type2 t2{};
    t2.getType<int>() = 100;
    t2.getType<int, 1>() = 200;
    t2.getType<int, 2>() = 300;
    std::cout << t2.getType<int>() << '\n';
    std::cout << t2.getType<int, 1>() << '\n';
    std::cout << t2.getType<int, 2>() << '\n';
}
