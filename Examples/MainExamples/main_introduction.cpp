#include "Examples/Benchmark.hpp"
#include "Taumaturgia/Object/DefaultStrategies.hpp"
#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Properties/Properties.hpp"

struct BaseType {
    std::string name{"BaseType"};
    Health hp{4};
};

struct MyType {
    std::string name{"MyType"};
};

using LivingType = add_properties<MyType, Living>;

int main() {
    BaseType baseType{};

    LivingType myType{};
#ifndef NO_PREMADE_PROPERTIES
    myType.getHealth() = Health{4};
#else
    traits::accessHealth::get(myType) = Health{4};
#endif

    auto test = [](auto& type) {
        Object object{type};
        std::cout << "Name: " << object.name() << '\n';
        std::cout << "Benchmark get hp directly.\n";
        const auto& hp2 = Benchmark([&] {
            Health& value = traits::accessHealth::get(type);
            value.addHealth(1);
            return value;
        })();
        std::cout << "Health = " << hp2.value();
        std::cout << '\n';

        std::cout << "Benchmark get hp from Object.\n";
        const auto& hp = Benchmark([&] {
            Health& value = getOpt<Parameter::Health>(object).value().get();
            value.addHealth(1);
            return value;
        })();
        std::cout << "Health = " << hp.value();
        std::cout << '\n';
    };

    test(baseType);
    std::cout << '\n';
    test(myType);
}
