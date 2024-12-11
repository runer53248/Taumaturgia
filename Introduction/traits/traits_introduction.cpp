#undef NO_PREMADE_PROPERTIES
#define NO_PREMADE_PROPERTIES

#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"

#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

#include "../pipeing/With.hpp"

// 1

struct Type1 {
    Name name{"Type1"};
};
static_assert(trait_accessable<Type1, Name>);
Type1 type_1{};

// 2

struct Type2 {
    Name name_{"Type2"};

public:
    decltype(auto) getName(this auto& self) { return (self.name_); }
    auto& getName() { return name_; }
    auto& getName() const { return name_; }
};
static_assert(trait_accessable<Type2, Name>);
Type2 type_2{};

// 3
struct Empty {};
auto type_3 =
    Empty{}         //
    | With::Damage  //
    | Create;       //
static_assert(trait_accessable<decltype(type_3), Damage>);

// 4

auto type_4 =
    Empty{}                             //
    | With::user_property<std::string>  //
    | Create;                           //
static_assert(trait_accessable<decltype(type_4), std::string>);

int main() {
    trait<Damage>::get(type_3) = Damage{5};
    trait<std::string>::get(type_4) = " Type4";

    std::cout << "value 1 = " << type_1.name << '\n';
    std::cout << "value 2 = " << type_2.getName() << '\n';
#ifndef NO_PREMADE_PROPERTIES
    std::cout << "value 3a = " << type_3.getDamage() << '\n';
#else
    std::cout << "value 3b = " << type_3.getType() << '\n';
#endif
    std::cout << "value 4 = " << type_4.getType() << '\n';
}
