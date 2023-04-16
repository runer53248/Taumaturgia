#pragma once
#include <iostream>

auto& operator<<(std::ostream& out, Damagingable auto& obj) {
    out << " for " << obj.dmg.value() << " dmg";
	out << " with " << static_cast<std::string>(obj.name);
    return out;
}

auto& operator<<(std::ostream& out, BodyLocation location) {
    switch(location) {
        case BodyLocation::Head:
            out << "Head";
        return out;
        case BodyLocation::Body:
            out << "Body";
        return out;
        case BodyLocation::Arms:
            out << "Arms";
        return out;
        case BodyLocation::Legs:
            out << "Legs";
        return out;
        case BodyLocation::Internal:
            out << "Internal";
        return out;
        case BodyLocation::ALL:
            out << "ALL";
        return out;
        default:
            out << "Unknown";
        return out;
    }
}

auto& operator<<(std::ostream& out, EffectType effect) {
    switch (effect) {
        case EffectType::Infection:
            out << " [Infection]";
            break;
        case EffectType::Sleep:
            out << " [sleep]";
            break;
        case EffectType::Daze:
            out << " [Daze]";
            break;
        case EffectType::Devour:
            out << " [devour]";
            break;
        case EffectType::Stun:
            out << " [stunned]";
            break;
        case EffectType::None:
            out << " [none]";
            break;
        default:
            out << " [unknown]";
            break;
    }
    return out;
}

auto& operator<<(std::ostream& out, Duration duration) {
    switch (duration.type()) {
        case DurationType::Day:
            out << " (" << duration.value() << " Days) ";
            break;
        case DurationType::Hour:
            out << " (" << duration.value() << " Hours) ";
            break;
        case DurationType::Minute:
            out << " (" << duration.value() << " Minutes) ";
            break;
        case DurationType::Round:
            out << " (" << duration.value() << " Rounds) ";
            break;
        case DurationType::Action:
            out << " (" << duration.value() << " Actions) ";
            break;
        case DurationType::Instant:
            out << " (" << duration.value() << " Instant) ";
            break;
    }
    return out;
}

auto print_hp = [](auto&& value) {
    auto& hp = value.get();
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(hp)>>) {
        std::cout << "[&]"; // value is reference_wraper to non const type - can be changed
    }

    std::cout << "(Hp: " << hp.value() << ")";
    if (not hp.effects().empty()) {
        for (const auto& effect : hp.effects()) {
            std::cout << effect.effectType();
            std::cout << effect.duration();
        }
    }
    std::cout << "";
    return std::optional{true};
};

auto print_cure_hp = [](auto&& value) {
    auto& cureHp = value.get();
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(cureHp)>>) {
        std::cout << "[&]";
    }

    std::cout << "(Cure Hp: " << cureHp.value() << ")";
    return std::optional{true};
};

auto print_ac = [](auto&& value) {
    auto& ac = value.get();
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(ac)>>) {
        std::cout << "[&]";
    }
    
    std::cout << " (Ac: " << ac.value() << " to " << ac.location() << ") ";

    if (not ac.protectEffects().empty()) {
        std::cout << "(protection";
        for (const auto& effect : ac.protectEffects()) {
            std::cout << effect;
        }
        std::cout << ") ";
    }
    
    return std::optional{true};
};

auto print_dmg = [](auto&& value) {
    auto& damage = value.get();
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(damage)>>) {
        std::cout << "[&]";
    }
    
    std::cout << "(Damage: " << damage.value() << damage.effect().effectType() << damage.effect().duration() << ")";
    return std::optional{true};
};

auto print_restore = [](auto&& value) {
    auto& effects = value.get();
    if constexpr (not std::is_const_v<std::remove_reference_t<decltype(effects)>>) {
        std::cout << "[&]";
    }
    
    std::cout << "(Restore: ";
    for (const auto& effect : effects) {
        std::cout << effect;
    }
    std::cout << ")";
    return std::optional<bool>{true};
};
auto print_person = [](const auto& person){
    std::cout << person.name();
    if (auto alive_opt = person.alive()) {
        if (alive_opt.value()) {
            std::cout << " [alive] ";
        } else {
            std::cout << " [dead] ";
        }
    } else {
        std::cout << " [unliving] ";
    }
    getOpt<Parameter::Ac>(person).and_then(print_ac);
    getOpt<Parameter::Hp>(person).and_then(print_hp);
    std::cout << '\n';
};

auto print_object_properties = [](const Object& obj) {
    std::cout << " name " << obj.name() << '\n';
    std::cout << " [can alive] " << obj.can_alive << '\n';
    std::cout << " [can attack] " << obj.can_attack << '\n';
    std::cout << " [can defend] " << obj.can_defend << '\n';
    std::cout << " [can get] " << obj.can_get << '\n';
    std::cout << " [can heal] " << obj.can_heal << '\n';
    std::cout << " [can restore] " << obj.can_restore << '\n';
    std::cout << '\n';
};

auto print_object = [](const auto& obj) {
    std::cout << " name " << obj.name() << '\n';

    if (obj.can_alive) {
        getOpt<Parameter::Hp>(obj).and_then(print_hp);
    }
    if (obj.can_attack) {
        getOpt<Parameter::Damage>(obj).and_then(print_dmg);
    }
    if (obj.can_defend) {
        getOpt<Parameter::Ac>(obj).and_then(print_ac);
    }
    if (obj.can_heal) {
        getOpt<Parameter::CureHp>(obj).and_then(print_cure_hp);
    }
    if (obj.can_restore) {
        getOpt<Parameter::Restore>(obj).and_then(print_restore);
    }
    std::cout << '\n';
};
