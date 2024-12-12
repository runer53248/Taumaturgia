#undef NO_PREMADE_PROPERTIES
// #define NO_PREMADE_PROPERTIES

#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Usage/With.hpp"

struct CustomName_1 {  // aggregate with custom type name
    Name other;
};

template <typename T>
    requires requires(T t) {
        { t.other } -> std::convertible_to<Name&>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.other);
    }
};

struct CustomName_2 {  // custom getter
    decltype(auto) name(this auto& self) { return (self.name_); }

private:
    Name name_;
};

template <typename T>
    requires requires(T t) {
        { t.name() } -> std::same_as<Name&>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};

struct CustomName_3 {  // no data stored in type
    auto name() & { return Name{"t_custom_name"}; }
    auto name() const& { return Name{"const t_custom_name"}; }
};

template <typename T>
    requires requires(T t) {
        { t.name() } -> std::same_as<Name>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};

int main() {
    {  // 1
        struct Type1 {
            Name name{"Type1"};
        };
        static_assert(trait_accessable<Type1, Name>);
        Type1 type_1{};
        std::cout << "value 1 = " << type_1.name << '\n';
        std::cout << "value 1 = " << type_1.name << '\n';
    }
    {  // 2
        struct Type2 {
            Name name_{"Type2"};

        public:
            // decltype(auto) getName(this auto& self) { return (self.name_); }
            auto& getName() { return name_; }
            auto& getName() const { return name_; }
        };
        static_assert(trait_accessable<Type2, Name>);
        Type2 type_2{};
        std::cout << "value 2 = " << type_2.getName() << '\n';
    }
    struct Empty {};
    {  // 3
        auto type_3 =
            Empty{}         //
            | With::Damage  //
            | Create;       //
        static_assert(trait_accessable<decltype(type_3), Damage>);
        trait<Damage>::get(type_3) = Damage{5};
#ifndef NO_PREMADE_PROPERTIES
        std::cout << "value 3a = " << type_3.getDamage() << '\n';
#else
        std::cout << "value 3b = " << type_3.getType() << '\n';
#endif
    }
    {  // 4
        auto type_4 =
            Empty{}                             //
            | With::user_property<std::string>  //
            | Create;                           //
        static_assert(trait_accessable<decltype(type_4), std::string>);
        trait<std::string>::get(type_4) = " Type4";
        std::cout << "value 4 = " << type_4.getType() << '\n';
    }
    {  // 5
        CustomName_1 type1{};
        CustomName_2 type2{};
        CustomName_3 type3{};

        static_assert(trait_accessable<decltype(type1), Name>);
        static_assert(trait_accessable<decltype(type2), Name>);
        static_assert(trait_accessable<decltype(type3), Name>);

        trait<Name>::get(type1) = Name{"test1"};
        trait<Name>::get(type2) = Name{"test2"};
        trait<Name>::get(type3) = Name{"test3"};

        auto value_1 = trait<Name>::get(type1);
        auto value_2 = trait<Name>::get(type2);
        auto value_3 = trait<Name>::get(type3);

        std::cout << "value 5.1 = " << value_1 << '\n';
        std::cout << "value 5.2 = " << value_2 << '\n';
        std::cout << "value 5.3 = " << value_3 << '\n';
    }
}
