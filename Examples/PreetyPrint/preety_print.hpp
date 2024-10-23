#pragma once
#include <iostream>
#include "Redirect.hpp"
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

template <typename T>
auto value_type(T&&) {
    constexpr bool is_ref = std::is_reference_v<T>;
    constexpr bool is_const = std::is_const_v<std::remove_reference_t<T>>;

    if constexpr (is_ref) {
        if constexpr (is_const) {
            return "[const&]";
        } else {
            return "[&]";
        }
    } else {
        if constexpr (is_const) {
            return "[const]";
        } else {
            return "[]";
        }
    }
}

struct {
    auto operator()(is_ref_wrapper_of_type<Health> auto&& value) const {
        auto& hp = value.get();
        std::cout << value_type(hp) << hp;
        return std::optional{value};
    }
} print_hp;

struct {
    auto operator()(is_ref_wrapper_of_type<CureHealth> auto&& value) const {
        auto& cureHealth = value.get();
        std::cout << value_type(cureHealth) << cureHealth;
        return std::optional{value};
    }
} print_cure_hp;

template <typename T>
concept WrappedProtectionOrArmorClass = is_ref_wrapper_of_type<T, ArmorClass> or is_ref_wrapper_of_type<T, Protection>;

struct {
    auto operator()(WrappedProtectionOrArmorClass auto&& value) const {
        auto& armor = value.get();  // can be either Protection or ArmorClass
        std::cout << value_type(armor) << armor;
        return std::optional{value};
    }
} print_protection;

struct {
    auto operator()(is_ref_wrapper_of_type<WearContainer> auto&& value) const {
        auto& armorWear = value.get();
        std::cout << value_type(armorWear) << armorWear;
        return std::optional{value}.and_then(print_new_line).and_then(print_tab);
    }
} print_wear;

struct {
    auto operator()(is_ref_wrapper_of_type<Damage> auto&& value) const {
        auto& damage = value.get();
        std::cout << value_type(damage) << damage;
        return std::optional{value};
    }
} print_dmg;

struct {
    auto operator()(is_ref_wrapper_of_type<EffectTypeContainer> auto&& value) const {
        auto& effects = value.get();
        std::cout << value_type(effects);
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
    // getOpt<Properties::Protection>(person).and_then(print_protection); // protection is now property of wearable items
    getOpt<Properties::Wear>(person).and_then(print_wear);
    getOpt<Properties::Health>(person).and_then(print_hp);
    getOpt<Properties::Restore>(person).and_then(print_restore);
    std::cout << '\n';
};

inline void print_object_properties(const Object& obj) {
    std::cout << "Name: " << obj.name() << '\n';
    std::cout << " [can get] " << obj.hasStrategyFor(Properties::Get) << '\n';
    // std::cout << " [can name] " << obj.hasStrategyFor(Properties::Name) << '\n';
    std::cout << " [can alive] " << obj.hasStrategyFor(Properties::Health) << '\n';
    std::cout << " [can attack] " << obj.hasStrategyFor(Properties::Damage) << '\n';
    std::cout << " [can defend] " << obj.hasStrategyFor(Properties::Protection) << '\n';
    std::cout << " [can heal] " << obj.hasStrategyFor(Properties::CureHealth) << '\n';
    std::cout << " [can restore] " << obj.hasStrategyFor(Properties::Restore) << '\n';
    std::cout << " [can wear] " << obj.hasStrategyFor(Properties::Wear) << '\n';
    std::cout << '\n';
};

inline void print_customized_properties(const auto& type) {
    const auto map = propertiesCustomizationMap<std::remove_cvref_t<decltype(type)>>();

    std::cout << " [custom get] " << map.at(Properties::Get) << '\n';
    // std::cout << " [custom name] " << map.at(Properties::Name) << '\n';
    std::cout << " [custom alive] " << map.at(Properties::Health) << '\n';
    std::cout << " [custom attack] " << map.at(Properties::Damage) << '\n';
    std::cout << " [custom defend] " << map.at(Properties::Protection) << '\n';
    std::cout << " [custom heal] " << map.at(Properties::CureHealth) << '\n';
    std::cout << " [custom restore] " << map.at(Properties::Restore) << '\n';
    std::cout << " [custom wear] " << map.at(Properties::Wear) << '\n';
    std::cout << '\n';
};

inline void print_object(const Object& obj) {
    std::cout << "Name: " << obj.name();
    print_liveable(obj);
    std::cout << '\n';

    // if (obj.hasStrategyFor(Properties::Name)) {
    // getOpt<Properties::Health>(obj).and_then(print_name).and_then(print_new_line);
    // }
    if (obj.hasStrategyFor(Properties::Health)) {
        getOpt<Properties::Health>(obj).and_then(print_hp).and_then(print_new_line);
    }
    if (obj.hasStrategyFor(Properties::Damage)) {
        getOpt<Properties::Damage>(obj).and_then(print_dmg).and_then(print_new_line);
    }
    if (obj.hasStrategyFor(Properties::Protection)) {
        getOpt<Properties::Protection>(obj).and_then(print_protection).and_then(print_new_line);
    }
    if (obj.hasStrategyFor(Properties::CureHealth)) {
        getOpt<Properties::CureHealth>(obj).and_then(print_cure_hp).and_then(print_new_line);
    }
    if (obj.hasStrategyFor(Properties::Restore)) {
        getOpt<Properties::Restore>(obj).and_then(print_restore).and_then(print_new_line);
    }
    if (obj.hasStrategyFor(Properties::Wear)) {
        getOpt<Properties::Wear>(obj).and_then(print_wear).and_then(print_new_line);
    }
    std::cout << '\n';
};
