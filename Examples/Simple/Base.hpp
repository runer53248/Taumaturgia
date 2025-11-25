#pragma once
#include <boost/pfr.hpp>

#include "UnorderedCtor.hpp"
#include "Usage/Properties.hpp"

struct Base_aggregate {
    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};
};

struct Base : public Base_aggregate {
    Base() noexcept = default;

    Base(int x, int y) noexcept
        : Base_aggregate(x, y) {}

    UnorderedCtor(Base);

    template <typename T, size_t = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (std::same_as<T, int>) {
            return (self.type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (self.type2);
        }
    }

    template <size_t S = 0, typename Self>
        requires(S < boost::pfr::tuple_size_v<Base_aggregate>)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using Base_agg = std::conditional_t<std::is_const_v<Self>,
                                            const Base_aggregate,
                                            Base_aggregate>;
        return boost::pfr::get<S>(static_cast<Base_agg&>(self));
    }

    template <size_t S, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        constexpr size_t agg_size = boost::pfr::tuple_size_v<Base_aggregate>;
        if constexpr (S == agg_size) {
            return (self.type1);
        }
        if constexpr (S == agg_size + 1) {
            return (self.type2);
        }
    }

private:
    int type1{};
    float type2{};
};
