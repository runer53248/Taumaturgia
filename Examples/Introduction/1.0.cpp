#include "Object/Concepts/Namingable.hpp"
// Namingable concepts is valif for types that:
/////////////////////////////////////////////////
// * type that have public name member convertible to std::string or const std::string

struct Valid_type_1 {
    const char* name{"Valid"};
};
static_assert(Namingable<Valid_type_1>);
/////////////////////////////////////////////////
#include <string>

struct Valid_type_2 {
    std::string name{"Valid"};
};
struct Valid_type_2_2 {
    const std::string name{"Valid"};
};
static_assert(Namingable<Valid_type_2>);
static_assert(Namingable<Valid_type_2_2>);
/////////////////////////////////////////////////
#include "Object/Concepts/Types/Name.hpp"

struct Valid_type_3 {
    Name name{"Valid"};
};
struct Valid_type_3_2 {
    const Name name{"Valid"};
};
static_assert(Namingable<Valid_type_3>);
static_assert(Namingable<Valid_type_3_2>);
/////////////////////////////////////////////////
// * type that have public getName method returning std::string convertible type

struct NoNameType {};

template <typename T, typename TYPE>
struct Valid_4 : T {
    Valid_4() = default;
    explicit Valid_4(const TYPE& name)
        : name{name} {}

    TYPE& getName() & {
        return name;
    }

    const TYPE& getName() const& {
        return name;
    }

private:
    TYPE name{"Valid"};
};
static_assert(Namingable<Valid_4<NoNameType, const char*>>);
static_assert(Namingable<Valid_4<NoNameType, std::string>>);
static_assert(Namingable<Valid_4<NoNameType, Name>>);
/////////////////////////////////////////////////
// * type resulted after gived Naming Properties

#include "Object/Properties/Naming.hpp"

using named_NoNameType = Naming<NoNameType>;
using named_Valid_type_1 = Naming<Valid_type_1>;
using named_Valid_type_2 = Naming<Valid_type_2>;
using named_Valid_type_3 = Naming<Valid_type_3>;

static_assert(Namingable<named_NoNameType>);
static_assert(Namingable<named_Valid_type_1>);
static_assert(Namingable<named_Valid_type_2>);
static_assert(Namingable<named_Valid_type_3>);

// Naming property is not propagated if type is already Namingable
static_assert(not std::is_same_v<named_NoNameType, NoNameType>);
static_assert(std::is_same_v<named_Valid_type_1, Valid_type_1>);
static_assert(std::is_same_v<named_Valid_type_2, Valid_type_2>);
static_assert(std::is_same_v<named_Valid_type_3, Valid_type_3>);
/////////////////////////////////////////////////
// * type that have CustomAccessName trait specialization

struct Valid_5 {
    auto name() & { return Name{"Valid_5"}; }
    auto name() const& { return Name{"const Valid_5"}; }
};

template <typename T>
    requires std::is_base_of_v<Valid_5, T>
struct traits::CustomAccessName<T> {
    static decltype(auto) get(auto& el) {
        return el.name();
    }
};
static_assert(Namingable<Valid_5>);
static_assert(std::is_same_v<Naming<Valid_5>, Valid_5>);
/////////////////////////////////////////////////
#include <iostream>

constexpr auto& operator<<(std::ostream& out, const Name& name) {
    return out << name.operator std::string();
}

int main() {
    Valid_type_1 type1{"Valid_type_1"};
    Valid_type_2 type2{"Valid_type_2"};
    Valid_type_3 type3{Name{"Valid_type_3"}};
    std::cout << "Take name from member:" << '\n';
    std::cout << "type1.name = " << type1.name << '\n';
    std::cout << "type2.name = " << type2.name << '\n';
    std::cout << "type3.name = " << type3.name << '\n';

    Valid_4<NoNameType, const char*> type4_1{"Valid_4_1"};
    Valid_4<NoNameType, std::string> type4_2{"Valid_4_2"};
    Valid_4<NoNameType, Name> type4_3{Name{"Valid_4_3"}};
    std::cout << "Take name from member by method:" << '\n';
    std::cout << "type4_1.getName() = " << type4_1.getName() << '\n';
    std::cout << "type4_2.getName() = " << type4_2.getName() << '\n';
    std::cout << "type4_3.getName() = " << type4_3.getName() << '\n';

    Valid_5 type5{};
    std::cout << "Take name by custom method:" << '\n';
    std::cout << "type5.name() = " << type5.name() << '\n';
    std::cout << "std::as_const(type5).name() = " << std::as_const(type5).name() << '\n';

    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "traits::accessName::get(type1) = " << traits::accessName::get(type1) << '\n';
    std::cout << "traits::accessName::get(type2) = " << traits::accessName::get(type2) << '\n';
    std::cout << "traits::accessName::get(type3) = " << traits::accessName::get(type3) << '\n';
    std::cout << "traits::accessName::get(type4_1) = " << traits::accessName::get(type4_1) << '\n';
    std::cout << "traits::accessName::get(type4_2) = " << traits::accessName::get(type4_2) << '\n';
    std::cout << "traits::accessName::get(type4_3) = " << traits::accessName::get(type4_3) << '\n';
    std::cout << "traits::accessName::get(type5) = " << traits::accessName::get(type5) << '\n';
    std::cout << "traits::accessName::get(std::as_const(type5)) = " << traits::accessName::get(std::as_const(type5)) << '\n';
    return 0;
}
