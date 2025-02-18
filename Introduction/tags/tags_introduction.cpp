#include <print>
#include "Examples/demangle_type_name.hpp"
#include "Usage/With.hpp"

#include "Introduction/parse_type_name.hpp"

struct Base {};

struct name_tag;
struct tag_2;

struct surname_tag;
struct address_tag;

int main() {
    // type for building properties - list containing result type and tags

    // building lists with same tags but different type
    using Int_name = list<int, name_tag>;
    using Float_name = list<float, name_tag>;

    using Name = list<std::string, name_tag>;  // building lists with duplicated type and tags

    using Name_2 = list<std::string, name_tag, tag_2>;  // building lists with duplicated type and one of it's tags
    // using Name_3 = list<std::string, tag_2, name_tag>;

    // building lists with same type but different tags
    using Surname = list<std::string, surname_tag>;
    using Address = list<std::string, address_tag>;
    using Info = list<std::string>;

    Name name{};
    Name_2 name_2{};
    Surname surname{};
    Address address{};
    Info info{};
    Int_name int_name{};
    Float_name float_name{};

    auto data =                                              // pipeing with create
        Base{}                                               //
        | With::user_property<int, name_tag>                 //
        | With::user_property<std::string, name_tag>         //
        | With::user_property<std::string, name_tag, tag_2>  //
        | With::user_property<std::string, surname_tag>      //
        | With::user_property<std::string, address_tag>      //
        | With::user_property<std::string>                   //
        | With::user_property<float, name_tag>               //
        | Create;

    auto data2 =                                             // pipeing creator
        From::base<Base>                                     //
        | With::user_property<int, name_tag>                 //
        | With::user_property<std::string, name_tag>         //
        | With::user_property<std::string, name_tag, tag_2>  //
        | With::user_property<std::string, surname_tag>      //
        | With::user_property<std::string, address_tag>      //
        | With::user_property<std::string>                   //
        | With::user_property<float, name_tag>               //
        ;

    auto data3 =                             //
        Base{}                               //
        | With::user_property_t<Int_name>    // build properties from list type
        | With::user_property_t<Name>        //
        | With::user_property_t<Name_2>      //
        | With::user_property_t<Surname>     //
        | With::user_property_t<Address>     //
        | With::user_property_t<Info>        //
        | With::user_property_t<Float_name>  //
        | Create;

    auto prop_list =                         //
        With::user_property_t<Int_name>      // property list
        | With::user_property_t<Name>        //
        | With::user_property_t<Name_2>      //
        | With::user_property_t<Surname>     //
        | With::user_property_t<Address>     //
        | With::user_property_t<Info>        //
        | With::user_property_t<Float_name>  //
        ;
    auto data4 = Base{} | prop_list;  // build properties from property list

    static_assert(std::same_as<decltype(data), decltype(data2)::result_type>);
    static_assert(std::same_as<decltype(data), decltype(data3)>);
    static_assert(std::same_as<decltype(data), decltype(data4)>);

    using Data = decltype(data);

    Data person{
        2500,
        "John",
        "Mark",
        "Smith",
        "Somewhere 12/7",
        "information text",
        18.35f,
    };

    constexpr auto seven_types =
        "int     = {}\n"
        "float   = {}\n"
        "Name    = {}\n"
        "Name 2  = {}\n"
        "Surname = {}\n"
        "Address = {}\n"
        "Info    = {}\n"
        "\n";

    std::println("getType<type, index>() - get property by type and it's index");
    std::print(
        seven_types,
        person.getType<int>(),
        person.getType<float>(),
        person.getType<std::string>(),
        person.getType<std::string, 1>(),
        person.getType<std::string, 2>(),
        person.getType<std::string, 3>(),
        person.getType<std::string, 4>());

    std::println("getTypeTaged<type, tags...>() - get property by type and it's tags");
    std::print(
        seven_types,
        person.getTypeTaged<int, name_tag>(),
        person.getTypeTaged<float, name_tag>(),
        person.getTypeTaged<std::string, name_tag>(),
        person.getTypeTaged<std::string, name_tag, tag_2>(),
        person.getTypeTaged<std::string, surname_tag>(),
        person.getTypeTaged<std::string, address_tag>(),
        person.getTypeTaged<std::string>());

    std::println("getTypeLike(list<type, tags...>{{}}) - get property by it's building list object");
    std::print(
        seven_types,
        person.getTypeLike(int_name),
        person.getTypeLike(float_name),
        person.getTypeLike(name),
        person.getTypeLike(name_2),
        person.getTypeLike(surname),
        person.getTypeLike(address),
        person.getTypeLike(info));

    std::println("getTypeLike<list<type, tags...>>() - get property by it's building list type");
    std::print(
        seven_types,
        person.getTypeLike<Int_name>(),
        person.getTypeLike<Float_name>(),
        person.getTypeLike<Name>(),
        person.getTypeLike<Name_2>(),
        person.getTypeLike<Surname>(),
        person.getTypeLike<Address>(),
        person.getTypeLike<Info>());

    std::println("getTaged<tags...>() / getTagedSKIP<index, tags...>() - get property by it's tags alone (with skipping for access toother types under same ones)");
    std::print(
        seven_types,
        person.getTaged<0, name_tag>(),  // same as: person.getTaged<name_tag>()
        person.getTaged<2, name_tag>(),
        person.getTaged<1, name_tag>(),
        person.getTaged<name_tag, tag_2>(),
        person.getTaged<surname_tag>(),
        person.getTaged<address_tag>(),
        person.getTaged());
    static_assert(&person.getTaged<0, name_tag>() == &person.getTaged<name_tag>());  // same reference

    // std::print("{}", ::name<Data>());
    std::print("{}", parse_type_name<Data>());
}
