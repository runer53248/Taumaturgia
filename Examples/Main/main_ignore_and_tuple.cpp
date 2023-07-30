#include "Examples/preety_print.hpp"
#include "basic_strategies.hpp"

struct Element2 {
    auto& getHp() & { return hp; }
    auto& getHp() const& { return hp; }

private:
    Health hp{100};
};

struct Element3 {};

int main() {
    std::vector<Object> elements;

    elements.push_back(Damaging<Naming<Element3>>{
        Name{"Test 1"},
        std::ignore});

    elements.push_back(Damaging<Wearing<Naming<Element3>>>{
        Name{"Test 2"},
        std::ignore,
        std::ignore});

    elements.push_back(
        Damaging<
            Wearing<
                Living<
                    Restoring<
                        Protecting<
                            Healing<
                                Naming<
                                    Element3>>>>>>>{
            Name{"Combo"},  // Naming
            Damage{20},     // Damaging
            std::ignore,    // Wearing
            Health{10},     // Living
            std::ignore,    // Restoring
            std::tuple{     // Protecting
                       15,
                       BodyLocation::Head,
                       std::initializer_list<EffectType>{
                           EffectType::Bleed,
                           EffectType::Daze}},
            std::ignore});  // Healing

    elements.push_back(Damaging<Naming<Element2>>{
        Name{"Element 2"},
        Damage{}});

    elements.push_back(Damaging<Naming<Element3>>{
        Name{"Element 3"},
        Damage{}});

    elements.push_back(Damaging<Healing<Naming<Element3>>>{
        Name{"Element 3 DamagingHealing"},
        std::tuple{
            5,
            DamageType::Divine,
            Effect{EffectType::Burn}},
        std::tuple{100}});

    elements.push_back(Healing<Damaging<Naming<Element3>>>{
        Name{"Element 3 HealingDamaging"},
        std::tuple{100},
        std::tuple{
            5,
            DamageType::Divine,
            Effect{EffectType::Burn}}});

    try {
        for (auto&& el : elements) {
            // print_object_properties(el);
            print_object(el);
        }
    } catch (const std::exception& err) {
        std::cout << err.what() << '\n';
    }
}
