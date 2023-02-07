#pragma once

auto print_hp = [](const auto& value) {
    const Hp& hp = Get<const Hp>(value);
    std::cout << "(Hp: " << hp.value() << ")\n";
    return std::optional{true};

    // return Visit<const Hp>(value).and_then([](const Hp& hp) {
    // 	std::cout << "(Hp: " << hp.value() << ")\n";
    // 	return std::optional{true};
    // });
};
auto print_cure_hp = [](const auto& value) {
    const Hp& cureHp = Get<const Hp>(value);
    std::cout << "(Cure Hp: " << cureHp.value() << ")\n";
    return std::optional{true};

    // return Visit<const Hp>(value).and_then([](const Hp& cureHp) {
    // 	std::cout << "(Cure Hp: " << cureHp.value() << ")\n";
    // 	return std::optional{true};
    // });
};
auto print_ac = [](const auto& value) {
    const AC& ac = Get<const AC>(value);
    std::cout << "(Ac: " << ac.value() << ") ";
    return std::optional{true};

    // return Visit<const AC>(value).and_then([](const AC& ac) {
    // 	std::cout << "(Ac: " << ac.value() << ") ";
    // 	return std::optional{true};
    // });
};
auto print_dmg = [](const auto& value) {
    const Damage& damage = Get<const Damage>(value);
    std::cout << "(Damage: " << damage.value() << ")\n";
    return std::optional{true};

    // return Visit<const Damage>(value).and_then([](const Damage& damage) {
    // 	std::cout << "(Damage: " << damage.value() << ")\n";
    // 	return std::optional{true};
    // });
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
    person.getConst(Parameter::Ac).and_then(print_ac);
    person.getConst(Parameter::Hp).and_then(print_hp);
};
