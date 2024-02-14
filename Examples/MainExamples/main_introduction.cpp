#include "../Benchmark.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"

struct MyType {
    std::string name{"My type"};
    // Health hp{4};  // can pass Livingable Concept
};

// using LivingType = Living<MyType>;
using LivingType = add_properties<MyType, Living>;

// static_assert(std::is_same_v<MyType, LivingType>);  // pass when MyType is Livingable

int main() {
    LivingType myType{};
    myType.getHp() = Health{4};
    const Object object{myType};

    std::cout << "Name: " << object.name() << '\n';

    std::cout << "Benchmark get hp from my type directly.\n";
    const auto& hp2 = Benchmark([&] {
        // return myType.hp;
        return myType.getHp();
    })();
    std::cout << "Health: " << hp2.value();
    std::cout << '\n';

    std::cout << "Benchmark get hp from object.\n";
    const auto& hp = Benchmark([&] {
        return getOpt<Parameter::Health>(object).value().get();  // GetStrategy_<Default>
    })();
    std::cout << "Health: " << hp.value();
    std::cout << '\n';
}
