#include <print>
#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Introduction/parse_type_name.hpp"

struct Base {};
struct int_tag;
struct float_tag;
struct name_tag;

constexpr auto default_int = 5;
constexpr auto default_int2 = 33;
constexpr auto default_float = 3.1416f;
constexpr auto default_name_tag = "Andre";

template <>
struct UserDefaultValue<int> {
    static constexpr auto value = [] { return default_int; };
};
template <>
struct UserDefaultValue<int, int_tag> {
    static constexpr auto value = [] { return default_int2; };
};
template <>
struct UserDefaultValue<float, float_tag> {
    static constexpr auto value = [] { return default_float; };
};
template <>
struct UserDefaultValue<std::string, name_tag> {
    static constexpr auto value = [] { return default_name_tag; };
};

int main() {
    using Int_name = list<int, int_tag>;
    using Float_name = list<float, float_tag>;
    using Name = list<std::string, name_tag>;

    constexpr auto x =                       // pipeing with create
        Base{}                               //
        | With::user_property<int>           //
        | With::user_property_t<Int_name>    //
        | With::user_property_t<Float_name>  //
        | Create;
    auto y =                           // pipeing with create
        Base{}                         //
        | With::user_property_t<Name>  //
        | Create;

    static_assert(x.getType<int>() == default_int);
    static_assert(x.getType<int, 1>() == default_int2);
    static_assert(x.getTaged<int_tag>() == default_int2);
    static_assert(x.getTypeOfSignature<Float_name>() == default_float);

    std::print("x.int   = {}\n", x.getType<int>());
    std::print("x.int2  = {}\n", x.getType<int, 1>());
    std::print("x.float = {}\n", x.getType<float>());
    std::print("y.name  = {}\n", y.getTypeOfSignature<Name>());
    std::println();

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
