#pragma once


#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        constexpr bool have_all_types_from_args = (trait_accessable<ClassName, std::remove_cvref_t<Args>> and ...);           \
        if constexpr (have_all_types_from_args) {                                                                             \
            ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                 \
        } else {                                                                                                              \
            static_assert(have_all_types_from_args, "Unordered c-tor arguments contains type not accessable by traits.");     \
        }                                                                                                                     \
    }

struct Base {
    Base() noexcept = default;
    TokenCtor(Base);

    template <typename T, size_t = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (std::same_as<T, int>) {
            return (self.type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (self.type2);
        }
        // if constexpr (std::same_as<T, double>) {
        //     return (self.type);
        // }
    }

    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};

private:
    // double type{};
    int type1{};
    float type2{};
};
