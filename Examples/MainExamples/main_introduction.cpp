#include "Examples/Benchmark.hpp"
#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Strategies/DefaultStrategies.hpp"

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
#ifdef NO_PREMADE_PROPERTIES
    Livingable_trait::get(myType) = Health{4};
#else
    myType.getHealth() = Health{4};
#endif

    auto test = [](auto& type) {
        Object object{type};
        std::cout << "Name: " << object.name() << '\n';
        std::cout << "\n- Benchmark get hp by Livingable_trait.\n";
        const auto& hp2 = Benchmark([&] {
            auto& value = Livingable_trait::get(type);
            value.addHealth(1);
            return value;
        })();
        std::cout << "Health = " << hp2.value();
        std::cout << '\n';

        std::cout << "\n- Benchmark get hp by Object::getOpt<Properties::Health>.\n";
        const auto& hp = Benchmark([&] {
            if (auto opt_hp_ref = getOpt<Properties::Health>(object); opt_hp_ref) {
                auto& value = opt_hp_ref.value().get();
                value.addHealth(1);
                return value;
            }
            throw std::logic_error("getOpt<Properties::Health> shouldn't fail.");
        })();
        std::cout << "Health = " << hp.value();
        std::cout << '\n';
    };

    test(baseType);
    std::cout << '\n';
    test(myType);
}
