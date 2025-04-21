#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"

// MARK: Item

struct Item {
    std::string name;
};

// MARK: Armor

class Armor {
public:
    Name name;

    Armor(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() { return protection; }
    const auto& getProtection() const { return protection; }

private:
    Protection protection;
};

// MARK: Weapon_A

struct Weapon_A {
    std::string name;
    Damage dmg;
};

// MARK: Weapon_B

class Weapon_B {
public:
    std::string name;

    Weapon_B(std::string name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& getDamage() { return dmg; }
    const auto& getDamage() const { return dmg; }

private:
    Damage dmg;
};

// MARK: Weapon_C

class Weapon_C {
public:
    std::string name;

    Weapon_C(const std::string& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& Dmg() { return dmg; }
    const auto& Dmg() const { return dmg; }

private:
    Damage dmg;
};

// MARK: traits::CustomAccessType<Damage, Weapon_C>

template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

// MARK: Player

struct Player {
    std::string name;
    WearContainer armorWear{10};
};

// MARK: Player_B

class Player_B {
public:
    WearContainer armorWear{10};

    Player_B(const std::string& name, Health hp)
        : name{name}, hp{hp} {}

    auto& Name() { return name; }
    const auto& Name() const { return name; }

    auto& getHealth() { return hp; }
    const auto& getHealth() const { return hp; }

private:
    std::string name;
    Health hp;
};

// MARK: CustomAccessType<Name, Player_B>

template <typename T>
    requires std::is_base_of_v<Player_B, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Name();
    }
};

// MARK: main

int main() {
    Object weaponA = Damaging<Weapon_A>{
        Name{"Sword A"},
        Damage{1,
               Effect{EffectType::Infection}}};
    Object weaponB = Damaging<Weapon_B>{
        Name{"Sword B"},
        Damage{5,
               Effect{EffectType::Infection}}};
    Object weaponC = Damaging<Weapon_C>{
        Name{"Sword C"},
        Damage{50,
               Effect{EffectType::Infection}}};

    // ! if Weapon_C was not Damagable then order of argument in c-tor will be different
    Object weapon_c2 = Damaging<Living<Weapon_C>>{
        Name{"Sword 2"},
        Health{100},
        Damage{10,
               Effect{
                   EffectType::Bleed,
                   Duration{5, DurationType::Round},
                   EffectState::Active}}};

    Object paladin = Living<Restoring<Healing<Player>>>{
        Name{"Paladin"},
        Health{100},
        EffectType::Infection,
        CureHealth{10}};  // will ignore Infection effects

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
            {EffectType::Bleed}}};

    Object chaimail = Armor{
        Name{"Chaimail"},
        ArmorClass{
            8,
            BodyLocation::Body,
            {EffectType::Daze}}};

    Object shield_2 = Armor{
        Name{"Shield 2"},
        ArmorClass{
            6,
            BodyLocation::Arms,
            {EffectType::Burn}}};

    auto print_info = [](auto& obj) {
        std::cout << obj.name() << " ";
        getOpt<Properties::Health, const Object>(obj)
            .and_then(print_hp);
        getOpt<Properties::Protection>(obj)
            .and_then(print_protection);
        getOpt<Properties::Wear>(obj)
            .and_then(print_wear);
        getOpt<Properties::Restore>(obj)
            .and_then(print_restore);
        std::cout << '\n';
    };

    std::cout << "print info:\n";
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "Warior wear armor:\n";
    defend(shield, &warior);
    defend(shield_2, &warior);
    defend(shield, &warior);
    defend(chaimail, &warior);
    print_info(warior);
    std::cout << "\n";

    std::cout << "- weapon A attack both:\n";
    print_object(weaponA);
    attack(weaponA, &weaponA, &paladin);
    attack(weaponA, &weaponA, &warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";
    std::cout << "- weapon B attack both:\n";
    print_object(weaponB);
    attack(weaponB, &weaponB, &paladin);
    attack(weaponB, &weaponB, &warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";
    std::cout << "- weapon C attack both:\n";
    print_object(weaponC);
    attack(weaponC, &weaponC, &paladin);
    attack(weaponC, &weaponC, &warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "- weapon 2 attack both:\n";
    print_object(weapon_c2);
    attack(weapon_c2, &paladin);
    attack(weapon_c2, &warior);
    print_info(paladin);
    print_info(warior);
    std::cout << "\n";

    std::cout << "Paladin restore from stun effect by potion use: \n";
    restore(potion, nullptr, &paladin);  // no owner needed by now
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin change shield: \n";
    getOpt<Properties::Wear>(paladin)
        .and_then([&](WearContainer& wear) {
            Protection& other_protection = getOpt<Properties::Protection>(shield_2).value().get();  // we now that it exist so don't check optional here

            auto opt_protection = wear.wearProtection(other_protection);  // change protection slot

            if (opt_protection) {
                std::cout << "Wear other armor: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(other_protection));
                std::cout << "\nin place of: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(opt_protection.value()));
                std::cout << '\n';
            }
            return std::optional{wear};
        });
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin remove all weared protection: \n";
    getOpt<Properties::Wear>(paladin)
        .and_then([&](WearContainer& wear) {  // remove all armor
            for (auto location : wear.getWearedLocations()) {
                auto opt_armor = wear.removeArmorAtLocation(location);
                if (opt_armor) {
                    std::cout << "remove armor:\n  ";  // TODO: get name of element (and add some ID)
                    print_protection(std::ref(opt_armor.value()));
                    std::cout << '\n';
                }
            }
            return std::optional{wear};
        });
    print_info(paladin);
    std::cout << '\n';

    for (const auto* entity : std::array{&paladin, &warior, &shield, &weaponA, &weaponB, &weaponC, &weapon_c2, &potion}) {
        print_properties(*entity);
        print_object(*entity);
    }
}
