#pragma once
#include <iostream>
#include "Taumaturgia/Object/Object.hpp"
#include "preety_print_types.hpp"

[[maybe_unused]] struct {
    template <typename T>
    auto operator()(std::reference_wrapper<T>&& value) const {
        std::cout << '\n';
        return std::optional{value};
    }
} print_new_line;

[[maybe_unused]] struct {
    template <typename T>
    auto operator()(std::reference_wrapper<T>&& value) const {
        std::cout << '\t';
        return std::optional{value};
    }
} print_tab;

void print_ref_sign(auto&& value) {
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(value)>>) {
        std::cout << "[&]";
    }
}

struct {
    auto operator()(WrappedType<Health> auto&& value) const {
        auto& hp = value.get();
        print_ref_sign(hp);
        std::cout << hp;
        return std::optional{value};
    }
} print_hp;

struct {
    auto operator()(WrappedType<CureHealth> auto&& value) const {
        auto& cureHealth = value.get();
        print_ref_sign(cureHealth);
        std::cout << cureHealth;
        return std::optional{value};
    }
} print_cure_hp;

template <typename T>
concept WrappedProtectionOrArmorClass = WrappedType<T, ArmorClass> or WrappedType<T, Protection>;

struct {
    auto operator()(WrappedProtectionOrArmorClass auto&& value) const {
        auto& armor = value.get();  // can be either Protection or ArmorClass
        print_ref_sign(armor);
        std::cout << armor;
        return std::optional{value};
    }
} print_protection;

struct {
    auto operator()(WrappedType<WearContainer> auto&& value) const {
        auto& armorWear = value.get();
        print_ref_sign(armorWear);
        std::cout << armorWear;
        return std::optional{value}.and_then(print_new_line).and_then(print_tab);
    }
} print_wear;

struct {
    auto operator()(WrappedType<Damage> auto&& value) const {
        auto& damage = value.get();
        print_ref_sign(damage);
        std::cout << damage;
        return std::optional{value};
    }
} print_dmg;

struct {
    auto operator()(WrappedType<EffectTypeContainer> auto&& value) const {
        auto& effects = value.get();
        print_ref_sign(effects);
        print_in_round_braces(
            std::cout, "Restore",
            [&] {
                std::cout << effects;
            });
        return std::optional{value};
    }
} print_restore;

inline void print_liveable(const Object& person) {
    if (auto alive_opt = person.alive()) {
        std::cout << alive_opt.value();
    } else {
        std::cout << " [unliving] ";
    }
};

inline void print_person(const Object& person) {
    std::cout << person.name();
    print_liveable(person);
    // getOpt<Parameter::Protection>(person).and_then(print_protection); // protection is now property of wearable items
    getOpt<Parameter::Wear>(person).and_then(print_wear);
    getOpt<Parameter::Health>(person).and_then(print_hp);
    getOpt<Parameter::Restore>(person).and_then(print_restore);
    std::cout << '\n';
};

inline void print_object_properties(const Object& obj) {
    std::cout << "Name: " << obj.name() << '\n';
    std::cout << " [can get] " << obj.can_get << '\n';
    std::cout << " [can alive] " << obj.can_alive << '\n';
    std::cout << " [can attack] " << obj.can_attack << '\n';
    std::cout << " [can defend] " << obj.can_defend << '\n';
    std::cout << " [can heal] " << obj.can_heal << '\n';
    std::cout << " [can restore] " << obj.can_restore << '\n';
    std::cout << " [can wear] " << obj.can_wear << '\n';
    std::cout << '\n';
};

inline void print_object(const Object& obj) {
    std::cout << "Name: " << obj.name();
    print_liveable(obj);
    std::cout << '\n';

    if (obj.can_alive) {
        getOpt<Parameter::Health>(obj).and_then(print_hp).and_then(print_new_line);
    }
    if (obj.can_attack) {
        getOpt<Parameter::Damage>(obj).and_then(print_dmg).and_then(print_new_line);
    }
    if (obj.can_defend) {
        getOpt<Parameter::Protection>(obj).and_then(print_protection).and_then(print_new_line);
    }
    if (obj.can_heal) {
        getOpt<Parameter::CureHealth>(obj).and_then(print_cure_hp).and_then(print_new_line);
    }
    if (obj.can_restore) {
        getOpt<Parameter::Restore>(obj).and_then(print_restore).and_then(print_new_line);
    }
    if (obj.can_wear) {
        getOpt<Parameter::Wear>(obj).and_then(print_wear).and_then(print_new_line);
    }
    std::cout << '\n';
};
