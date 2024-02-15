#include "../../Object/Concepts/Namingable.hpp"

/////////////////////////////////////////////////
struct Valid_type_1 {
    const char* name{"Valid"};
};
static_assert(Namingable<Valid_type_1>);
/////////////////////////////////////////////////
#include <string>

struct Valid_type_2 {
    std::string name{"Valid"};
};
static_assert(Namingable<Valid_type_2>);
/////////////////////////////////////////////////
#include "../../Object/Concepts/Types/Name.hpp"

struct Valid_type_3 {
    Name name{"Valid"};
};
static_assert(Namingable<Valid_type_3>);
/////////////////////////////////////////////////
struct NoNameType {};

template <typename T, typename TYPE>
struct Valid_4 : T {
    TYPE& getName() & {
        return name;
    }

    const TYPE& getName() const & {
        return name;
    }

private:
    TYPE name{"Valid"};
};
static_assert(Namingable<Valid_4<NoNameType, const char*>>);
static_assert(Namingable<Valid_4<NoNameType, std::string>>);
static_assert(Namingable<Valid_4<NoNameType, Name>>);
/////////////////////////////////////////////////
#include "../../Object/Properties/Naming.hpp"

static_assert(Namingable<Naming<NoNameType>>);
static_assert(Namingable<Naming<Valid_type_1>>);
static_assert(Namingable<Naming<Valid_type_2>>);
static_assert(Namingable<Naming<Valid_type_3>>);

static_assert(not std::is_same_v<Naming<NoNameType>, NoNameType>);
static_assert(std::is_same_v<Naming<Valid_type_1>, Valid_type_1>);
static_assert(std::is_same_v<Naming<Valid_type_2>, Valid_type_2>);
static_assert(std::is_same_v<Naming<Valid_type_3>, Valid_type_3>);
/////////////////////////////////////////////////
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Name& name) {
    out << name.operator std::string();
    return out;
}

int main() {
    Valid_type_1 type1;
    Valid_type_2 type2;
    Valid_type_3 type3;
    std::cout << "Take name from member:" << '\n';
    std::cout << type1.name << '\n';
    std::cout << type2.name << '\n';
    std::cout << type3.name << '\n';

    Valid_4<NoNameType, const char*> type4_1;
    Valid_4<NoNameType, std::string> type4_2;
    Valid_4<NoNameType, Name> type4_3;
    std::cout << "Take name from member by method:" << '\n';
    std::cout << type4_1.getName() << '\n';
    std::cout << type4_2.getName() << '\n';
    std::cout << type4_3.getName() << '\n';

    std::cout << "Take name from by access trait:" << '\n';
    std::cout << traits::accessName::get(type1) << '\n';
    std::cout << traits::accessName::get(type2) << '\n';
    std::cout << traits::accessName::get(type3) << '\n';
    std::cout << traits::accessName::get(type4_1) << '\n';
    std::cout << traits::accessName::get(type4_2) << '\n';
    std::cout << traits::accessName::get(type4_3) << '\n';
    return 0;
}
