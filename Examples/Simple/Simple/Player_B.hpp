#pragma once

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
