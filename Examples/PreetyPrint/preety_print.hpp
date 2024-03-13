#pragma once
#include <iostream>
#include "Object/Object.hpp"
#include "preety_print_types.hpp"

[[maybe_unused]] struct {
    template <typename T>
    auto operator()(std::reference_wrapper<T>&& value) const {
        std::cout << '\n';
        return std::optional{value};
    }
} print_new_line;

struct {
    auto operator()(WrappedType<Health> auto&& value) const {
        auto& hp = value.get();
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(hp)>>) {
            std::cout << "[&]";  // value is reference_wrapper to non const type - can be changed
        }

        std::cout << "(Health: " << hp.value();
        if (hp.value() == hp.maxValue()) {
            std::cout << " MAX";
        }
        std::cout << ")";
        if (not hp.effects().empty()) {
            std::cout << " {Effects: ";
            for (const auto& effect : hp.effects()) {
                std::cout << effect.effectType();
                std::cout << effect.duration();
            }
            std::cout << "}";
        }
        return std::optional{value};
    }
} print_hp;

struct {
    auto operator()(WrappedType<CureHealth> auto&& value) const {
        auto& cureHealth = value.get();
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(cureHealth)>>) {
            std::cout << "[&]";
        }

        std::cout << "(Cure Health: " << cureHealth.value() << toString(cureHealth.valueType()) << ")";
        return std::optional{value};
    }
} print_cure_hp;

template <typename T>
concept WrappedProtectionOrArmorClass = WrappedType<T, ArmorClass> or WrappedType<T, Protection>;

struct {
    auto operator()(WrappedProtectionOrArmorClass auto&& value) const {
        auto& armor = value.get();  // can be either Protection or ArmorClass
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(armor)>>) {
            std::cout << "[&]";
        }

        std::cout << "(Ac: " << armor.armorClass() << " to " << armor.location() << ") ";

        if (not armor.protectEffects().empty()) {
            std::cout << "(protection";
            for (const auto& effect : armor.protectEffects()) {
                std::cout << effect;
            }
            std::cout << ") ";
        }

        return std::optional{value};
    }
} print_protection;

struct {
    auto operator()(WrappedType<ProtectionContainer> auto&& value) const {
        auto& armorWear = value.get();
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(armorWear)>>) {
            std::cout << "[&]";
        }

        std::cout << "(armor class: " << armorWear.value() << ") ";

        if (not armorWear.protectEffects().empty()) {
            std::cout << "(protection";
            for (const auto& effect : armorWear.protectEffects()) {
                std::cout << effect;
            }
            std::cout << ") ";
        }

        return std::optional{value};
    }
} print_wear;

struct {
    auto operator()(WrappedType<Damage> auto&& value) const {
        auto& damage = value.get();
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(damage)>>) {
            std::cout << "[&]";
        }

        std::cout << "(Damage: " << damage.value() << damage.type() << damage.effect().effectType() << damage.effect().duration();
        std::cout << damage.effect().state().effectState();
        std::cout << ")";
        return std::optional{value};
    }
} print_dmg;

struct {
    auto operator()(WrappedType<EffectTypeContainer> auto&& value) const {
        auto& effects = value.get();
        if constexpr (not std::is_const_v<std::remove_reference_t<decltype(effects)>>) {
            std::cout << "[&]";
        }

        std::cout << "(Restore:";
        for (const auto& effect : effects) {
            std::cout << effect;
        }
        std::cout << ")";
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
