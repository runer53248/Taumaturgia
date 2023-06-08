#include <vector>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "preety_print.hpp"

struct Item {
    std::string name;
};

struct Armor {
    Name name;

    Armor(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() {
        return protection;
    }

    const auto& getProtection() const {
        return protection;
    }

private:
    Protection protection;
};

struct Weapon_A {
    std::string name;
    Damage dmg;
};

struct Weapon_B {
    std::string name;

    Weapon_B(std::string name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& getDmg() {
        return dmg;
    }

    const auto& getDmg() const {
        return dmg;
    }

private:
    Damage dmg;
};

struct Weapon_C {
    std::string name;

    Weapon_C(const std::string& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& Dmg() {
        return dmg;
    }

    const auto& Dmg() const {
        return dmg;
    }

private:
    Damage dmg;
};

template <>
struct traits::customAccessDamage<Weapon_C> {
    static auto& get(auto& el) {
        return el.Dmg();
    }
};

struct Player {
    std::string name;
    ProtectionContainer armorWear{10};
};

struct Player_B {
    ProtectionContainer armorWear{10};

    Player_B(const std::string& name, Health hp)
        : name{name}, hp{hp} {}

    auto& Name() {
        return name;
    }

    const auto& Name() const {
        return name;
    }

    auto& getHp() {
        return hp;
    }

    const auto& getHp() const {
        return hp;
    }

private:
    std::string name;
    Health hp;
};

template <>
struct traits::customAccessName<Player_B> {
    static auto& get(auto& el) {
        return el.Name();
    }
};

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon_C>{
        Name{"Sword"},
        Damage{50,
               Effect{EffectType::Infection}}};

    Object weapon_2 = Damaging<Weapon_C>{
        Name{"Sword 2"},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   State{EffectState::Active}}}};

    Object paladin = Living<Restoring<Healing<Player>>>{
        Name{"Paladin"},
        Health{100},
        EffectType::Infection,
        Health{10}};  // will ignore Infection effects

    Object warior = Living<Player_B>{
        Name{"Warior"},
        Health{100}};

    Object potion = Restoring<Item>{
        Name{"Potion"},
        EffectType::Stun};

    Object shield = Armor{
        Name{"Shield"},
        ArmorClass{
            4,
            BodyLocation::Arms,
            {EffectType::Bleed}}};  // will protect against Bleed effects

    Object chaimail = Armor{
        Name{"Chaimail"},
        ArmorClass{
            8,
            BodyLocation::Body,
            {EffectType::Daze}}};  // will protect against Daze effects

    Object shield_2 = Armor{
        Name{"Shield 2"},
        ArmorClass{
            6,
            BodyLocation::Arms,
            {EffectType::Burn}}};  // will protect against Burn effects

    container.push_back(Item{});

    auto print_info = [](auto& obj) {
        std::cout << obj.name() << " ";
        getOpt<Parameter::Health, const Object>(obj)
            .and_then(print_hp);
        getOpt<Parameter::Protection>(obj)
            .and_then(print_protection);
        getOpt<Parameter::Wear>(obj)
            .and_then(print_wear);
        getOpt<Parameter::Restore>(obj)
            .and_then(print_restore);
        std::cout << '\n';
    };

    std::cout << "print info:\n";
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "Paladin wear armor:\n";
    shield.defend(&paladin);
    shield_2.defend(&paladin);
    shield.defend(&paladin);
    chaimail.defend(&paladin);
    print_info(paladin);
    std::cout << "\n";

    std::cout << "weapon attack both:\n";
    weapon.attack(&weapon, &paladin);
    weapon.attack(&weapon, &warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "weapon 2 attack both:\n";
    weapon_2.attack(&paladin);
    weapon_2.attack(&warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "Paladin restore from stun effect by potion use: \n";
    potion.restore(nullptr, &paladin);  // no owner needed by now
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin change shield: \n";
    getOpt<Parameter::Wear>(paladin)
        .and_then([&](ProtectionContainer& wear) {
            Protection& other_protection = getOpt<Parameter::Protection>(shield_2).value().get();  // we now that it exist so don't check optional here

            auto opt_protection = wear.wearProtection(other_protection);  // change protection slot

            if (opt_protection) {
                std::cout << "Wear other armor: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(other_protection));
                std::cout << "\nin place of: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(opt_protection.value()));
                std::cout << '\n';
            }
            return std::optional{true};
        });
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin remove all weared protection: \n";
    getOpt<Parameter::Wear>(paladin)
        .and_then([&](ProtectionContainer& wear) {  // remove all armor
            for (auto location : wear.getWearedLocations()) {
                auto opt_armor = wear.removeArmorAtLocation(location);
                if (opt_armor) {
                    std::cout << "remove armor:\n  ";  // TODO: get name of element (and add some ID)
                    print_protection(std::ref(opt_armor.value()));
                    std::cout << '\n';
                }
            }
            return std::optional{true};
        });
    print_info(paladin);
    std::cout << '\n';

    print_object_properties(paladin);
    print_object(paladin);

    print_object_properties(warior);
    print_object(warior);

    print_object_properties(shield);
    print_object(shield);

    print_object_properties(weapon);
    print_object(weapon);

    print_object(weapon_2);

    print_object(potion);
}
