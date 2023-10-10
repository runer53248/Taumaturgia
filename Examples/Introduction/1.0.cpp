struct Valid_type_1 {
    const char* name{"Valid"};
};

#include <string>

struct Valid_type_2 {
    std::string name{"Valid"};
};

#include "../../Object/Concepts/Types/Name.hpp"

struct Valid_type_3 {
    Name name{"Valid"};
};

std::ostream& operator<<(std::ostream& out, const Name& name) {
    out << name.operator std::string();
    return out;
}

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

#include "../../Object/Concepts/Namingable.hpp"

static_assert(Namingable<Valid_type_1>);
static_assert(Namingable<Valid_type_2>);
static_assert(Namingable<Valid_type_3>);
static_assert(Namingable<Valid_4<NoNameType, const char*>>);
static_assert(Namingable<Valid_4<NoNameType, std::string>>);
static_assert(Namingable<Valid_4<NoNameType, Name>>);

#include "../../Object/Properties/Naming.hpp"

static_assert(Namingable<Naming<NoNameType>>);
static_assert(Namingable<Naming<Valid_type_1>>);
static_assert(Namingable<Naming<Valid_type_2>>);
static_assert(Namingable<Naming<Valid_type_3>>);

static_assert(std::is_same_v<Naming<Valid_type_1>, Valid_type_1>);
static_assert(std::is_same_v<Naming<Valid_type_2>, Valid_type_2>);
static_assert(std::is_same_v<Naming<Valid_type_3>, Valid_type_3>);

#include <iostream>

int main() {
    Valid_type_1 type1;
    Valid_type_2 type2;
    Valid_type_3 type3;
    std::cout << type1.name << '\n';
    std::cout << type2.name << '\n';
    std::cout << type3.name << '\n';
pclose
    Valid_4<NoNameType, const char*> type4_1;
    Valid_4<NoNameType, std::string> type4_2;
    Valid_4<NoNameType, Name> type4_3;
    std::cout << type4_1.getName() << '\n';
    std::cout << type4_2.getName() << '\n';
    std::cout << type4_3.getName() << '\n';
    return 0;
}
