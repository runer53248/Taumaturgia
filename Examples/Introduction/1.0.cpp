#include "Usage/Traits.hpp"

constexpr auto default_name = "Valid";

// Namingable concepts is valid for types that:
/////////////////////////////////////////////////
// * type that have public name member convertible to std::string or const std::string

// MARK: t_simple_name

struct t_simple_name {
    const char* name{default_name};
};
static_assert(Namingable<t_simple_name>);
/////////////////////////////////////////////////
#include <string>

// MARK: t_string_name

struct t_string_name {
    std::string name{default_name};
};

// MARK: t_const_string_name

struct t_const_string_name {
    const std::string name{default_name};
};
static_assert(Namingable<t_string_name>);
static_assert(Namingable<t_const_string_name>);
/////////////////////////////////////////////////
#include "Usage/Types/Name/Name.hpp"

// MARK: t_Name_name

struct t_Name_name {
    Name name{default_name};
};

// MARK: t_const_Name_name

struct t_const_Name_name {
    const Name name{default_name};
};
static_assert(Namingable<t_Name_name>);
static_assert(Namingable<t_const_Name_name>);
/////////////////////////////////////////////////
// * type that have public getName method returning std::string convertible type

struct t_empty {};

// MARK: t_getName_property

template <typename T, typename TYPE>
class t_getName_property : public T {
public:
    t_getName_property() = default;
    explicit t_getName_property(const TYPE& name)
        : name{name} {}

    TYPE& getName() & {
        return name;
    }

    const TYPE& getName() const& {
        return name;
    }

private:
    TYPE name{default_name};
};
static_assert(Namingable<t_getName_property<t_empty, const char*>>);
static_assert(Namingable<t_getName_property<t_empty, std::string>>);
static_assert(Namingable<t_getName_property<t_empty, Name>>);
/////////////////////////////////////////////////
// * type resulted after gived Naming Properties

#include "Usage/Premade/Properties/Naming.hpp"

// MARK: t_Naming_t_empty

using t_Naming_t_empty = Naming<t_empty>;
using t_Naming_t_simple_name = Naming<t_simple_name>;
using t_Naming_t_string_name = Naming<t_string_name>;
using t_Naming_t_Name_name = Naming<t_Name_name>;

static_assert(not Namingable<t_empty>);
static_assert(Namingable<t_simple_name>);
static_assert(Namingable<t_string_name>);
static_assert(Namingable<t_Name_name>);

// Naming property is not propagated if type is already Namingable
static_assert(not std::is_same_v<t_Naming_t_empty, t_empty>);
static_assert(std::is_same_v<t_Naming_t_simple_name, t_simple_name>);
static_assert(std::is_same_v<t_Naming_t_string_name, t_string_name>);
static_assert(std::is_same_v<t_Naming_t_Name_name, t_Name_name>);
/////////////////////////////////////////////////
// * type that have CustomAccessName trait specialization

// MARK: t_custom_name

struct t_custom_name {
    auto name() & { return Name{"t_custom_name"}; }
    auto name() const& { return Name{"const t_custom_name"}; }
};

template <typename T>
    requires std::is_base_of_v<t_custom_name, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.name();
    }
};
static_assert(Namingable<t_custom_name>);
static_assert(std::is_same_v<Naming<t_custom_name>, t_custom_name>);
/////////////////////////////////////////////////
#include <iostream>

auto& operator<<(std::ostream& out, const Name& name) {
    return out << static_cast<std::string>(name);
}

// MARK: main

int main() {
    t_simple_name type1{"t_simple_name"};
    t_string_name type2{"t_string_name"};
    t_Name_name type3{Name{"t_Name_name"}};

    std::cout << '\n';
    std::cout << "Take name from member:" << '\n';
    std::cout << "type1.name = " << type1.name << '\n';
    std::cout << "type2.name = " << type2.name << '\n';
    std::cout << "type3.name = " << type3.name << '\n';

    t_getName_property<t_empty, const char*> type4_1{"t_getName_simple"};
    t_getName_property<t_empty, std::string> type4_2{"t_getName_string"};
    t_getName_property<t_empty, Name> type4_3{Name{"t_getName_Name"}};

    std::cout << '\n';
    std::cout << "Take name from member by method:" << '\n';
    std::cout << "type4_1.getName() = " << type4_1.getName() << '\n';
    std::cout << "type4_2.getName() = " << type4_2.getName() << '\n';
    std::cout << "type4_3.getName() = " << type4_3.getName() << '\n';

    t_custom_name type5{};
    std::cout << '\n';
    std::cout << "Take name by custom method:" << '\n';
    std::cout << "type5.name() = " << type5.name() << '\n';
    std::cout << "std::as_const(type5).name() = " << std::as_const(type5).name() << '\n';

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type1) = " << trait<Name>::get(type1) << '\n';
    std::cout << "trait<Name>::get(type2) = " << trait<Name>::get(type2) << '\n';
    std::cout << "trait<Name>::get(type3) = " << trait<Name>::get(type3) << '\n';
    std::cout << "trait<Name>::get(type4_1) = " << trait<Name>::get(type4_1) << '\n';
    std::cout << "trait<Name>::get(type4_2) = " << trait<Name>::get(type4_2) << '\n';
    std::cout << "trait<Name>::get(type4_3) = " << trait<Name>::get(type4_3) << '\n';
    std::cout << "trait<Name>::get(type5) = " << trait<Name>::get(type5) << '\n';
    std::cout << "trait<Name>::get(std::as_const(type5)) = " << trait<Name>::get(std::as_const(type5)) << '\n';
    return 0;
}
