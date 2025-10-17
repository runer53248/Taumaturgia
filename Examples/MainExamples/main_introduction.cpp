#include "Examples/Benchmark.hpp"
#include "Examples/Checks.hpp"
#include "Usage/DefaultStrategies.hpp"

struct BaseType {
    std::string name{"BaseType"};
    Health hp{4};
};

struct MyType {
    std::string name{"MyType"};
};

using LivingType = add_properties_ordered<
    MyType,
    Living>;

int main() {
    BaseType baseType{};

    LivingType myType{};

    // trait<Health>::get(myType) = Health{4};
    myType.getType<Health>() = Health{4};

    auto test = [](auto& type) {
        Object object{type};
        std::cout << "Name: " << object.name() << '\n';
        std::cout << "\n- Benchmark get hp by trait<Health>.\n";
        const auto& hp2 = Benchmark([&] {
            auto& value = trait<Health>::get(type);
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

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
