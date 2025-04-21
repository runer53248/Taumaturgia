#include <print>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Base {};
struct protection_tag;

int main() {
    // when (With::Protection) != (With::user_property<Protection>)
    // then user_property<Protection> and user_property<Protection, protection_tag> are not in order list
    auto test1 =
        Base{}                                             //
        | With::user_property<Protection>                  //
        | With::user_property<Protection, protection_tag>  //
        | With::Protection                                 //
        | Create;
    auto test2 =
        Base{}                                             //
        | With::user_property<Protection, protection_tag>  //
        | With::user_property<Protection>                  //
        | With::Protection                                 //
        | Create;
    auto test3 =
        Base{}                                             //
        | With::user_property<Protection>                  //
        | With::Protection                                 //
        | With::user_property<Protection, protection_tag>  //
        | Create;
    auto test4 =
        Base{}                                             //
        | With::user_property<Protection, protection_tag>  //
        | With::Protection                                 //
        | With::user_property<Protection>                  //
        | Create;
    auto test5 =
        Base{}                                             //
        | With::Protection                                 //
        | With::user_property<Protection>                  //
        | With::user_property<Protection, protection_tag>  //
        | Create;
    auto test6 =
        Base{}                                             //
        | With::Protection                                 //
        | With::user_property<Protection, protection_tag>  //
        | With::user_property<Protection>                  //
        | Create;
    std::print("\n\n");
    std::print("test1 = {}\n", ::name<decltype(test1)>());
    std::print("test2 = {}\n", ::name<decltype(test2)>());
    std::print("test3 = {}\n", ::name<decltype(test3)>());
    std::print("test4 = {}\n", ::name<decltype(test4)>());
    std::print("test5 = {}\n", ::name<decltype(test5)>());
    std::print("test6 = {}\n", ::name<decltype(test6)>());

    auto test7 =
        Base{}                                             //
        | With::user_property<Protection, protection_tag>  //
        | With::Protection                                 //
        | Create;
    auto test8 =
        Base{}                                             //
        | With::Protection                                 //
        | With::user_property<Protection, protection_tag>  //
        | Create;
    static_assert(std::same_as<
                  decltype(test7),
                  decltype(test8)>);
    std::print("\n");
    std::print("test7 = {}\n", ::name<decltype(test7)>());
    std::print("test8 = {}\n", ::name<decltype(test8)>());
}
