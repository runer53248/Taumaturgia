#pragma once

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

auto print_hp = [](const auto& value) {
    if constexpr (not std::is_same_v<std::remove_cvref_t<decltype(value)>, get_const_result_type>) {
        std::cout << "[&]"; // value is reference_wraper to non const type - can be changed
    }
    const Hp& hp = Get<Hp>(value);
    std::cout << "(Hp: " << hp.value() << ")";
    if (hp.effect() != AttackEffect::None) {
        switch(hp.effect().effect()){
            case AttackEffect::Sleep:
                std::cout << " [sleep effect]";
                break;
            case AttackEffect::Devour:
                std::cout << " [devour]";
                break;
            case AttackEffect::Stun:
                std::cout << " [stunned]";
                break;
            default:
                break;
        }
        if (hp.effect().duration().type == DurationType::Round) {
            std::cout << " (" << hp.effect().duration().value << " rounds) ";
        }
    }

    std::cout << "\n";
    return std::optional{true};
};
auto print_cure_hp = [](const auto& value) {
    if constexpr (not std::is_same_v<std::remove_cvref_t<decltype(value)>, get_const_result_type>) {
        std::cout << "[&]";
    }
    const Hp& cureHp = Get<Hp>(value);
    std::cout << "(Cure Hp: " << cureHp.value() << ")\n";
    return std::optional{true};
};
auto print_ac = [](const auto& value) {
    if constexpr (not std::is_same_v<std::remove_cvref_t<decltype(value)>, get_const_result_type>) {
        std::cout << "[&]";
    }
    const AC& ac = Get<AC>(value);
    std::cout << "(Ac: " << ac.value() << ") ";
    return std::optional{true};
};
auto print_dmg = [](const auto& value) {
    if constexpr (not std::is_same_v<std::remove_cvref_t<decltype(value)>, get_const_result_type>) {
        std::cout << "[&]";
    }
    const Damage& damage = Get<Damage>(value);
    std::cout << "(Damage: " << damage.value() << ")\n";
    return std::optional{true};
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
    get(person, Parameter::Ac).and_then(print_ac);
    get(person, Parameter::Hp).and_then(print_hp);
};
