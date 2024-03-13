#include "Examples/Benchmark.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"

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
    myType.getHealth() = Health{4};

    int healthValue = 1;

    auto test = [&](auto& type) {
        Object object{type};
        std::cout << "Name: " << object.name() << '\n';
        std::cout << "Benchmark get hp directly.\n";
        const auto& hp2 = Benchmark([&] {
            if constexpr (traits::HealthAccessable<std::remove_cvref_t<decltype(type)>>) {
                return type.hp = Health{healthValue++};
            } else {
                return type.getHealth() = Health{healthValue++};
            }
        })();
        std::cout << "Health = " << hp2.value();
        std::cout << '\n';

        std::cout << "Benchmark get hp from Object.\n";
        const auto& hp = Benchmark([&] {
            return getOpt<Parameter::Health>(object).value().get() = Health{healthValue++};  // GetStrategy_<Default>
        })();
        std::cout << "Health = " << hp.value();
        std::cout << '\n';
    };

    test(baseType);
    std::cout << '\n';
    test(myType);
}
