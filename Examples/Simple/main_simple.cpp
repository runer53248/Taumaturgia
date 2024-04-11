#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Strategies/DefaultStrategies.hpp"

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

    auto& getDmg() { return dmg; }
    const auto& getDmg() const { return dmg; }

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

// MARK: CustomAccessDamage<Weapon_C>

template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessDamage<T> {
    static decltype(auto) get(auto& el) {
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

// MARK: CustomAccessName<Player_B>

template <typename T>
    requires std::is_base_of_v<Player_B, T>
struct traits::CustomAccessName<T> {
    static decltype(auto) get(auto& el) {
        return el.Name();
    }
};

// MARK: main

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon_C>{
        Name{"Sword"},
        Damage{50,
               Effect{EffectType::Infection}}};

    // ! if Weapon_C was not Damagable then order of argument in c-tor will be different
    Object weapon_2 = Damaging<Living<Weapon_C>>{
        Name{"Sword 2"},
        Health{100},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   State{EffectState::Active}}}};

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
