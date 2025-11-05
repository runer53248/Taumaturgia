#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct extra_token {};

struct Base {
    Health hp;
    // Damage dmg;
    Data<int, extra_token> type;

    template <size_t DIG, typename Self>
        requires(DIG < boost::pfr::tuple_size_v<Self>)
    decltype(auto) getType(this Self& self) {
        return boost::pfr::get<DIG>(self);
    }
};

// MARK: UserDefaultValue

template <>
struct UserDefaultValue<Damage, extra_token> {
    static constexpr auto value = [] { return Damage{500}; };
};

// MARK: operator<<

template <typename T, typename Tags>
auto& operator<<(std::ostream& out, Data<T, Tags> status) {
    out << status.value;
    return out;
}

// MARK: std::formatter

template <>
struct std::formatter<Data<int, extra_token>> : std::formatter<std::string> {
    auto format(const Data<int, extra_token>& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << t;
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

// MARK: to_tuple

template <typename T>
auto to_tuple(T&& type) {
    using TUPLE = as_tuple<std::remove_cvref_t<T>>;
    constexpr size_t count = std::tuple_size_v<TUPLE>;
    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        return TUPLE{type.template getType<idx>()...};
    }(std::make_index_sequence<count>{});
};

// MARK: for_each_type

auto for_each_type = []<typename T, typename Fn>(T&& type, Fn fn) {
    using TUPLE = as_tuple<std::remove_cvref_t<T>>;
    constexpr size_t count = std::tuple_size_v<TUPLE>;

    auto getWay = []<size_t N, typename TT>(TT&& type) {
        if constexpr (requires { getType<N>(std::declval<TT>()); }) {
            return getType<N>(std::forward<TT>(type));
        } else if constexpr (requires { std::get<N>(std::declval<TT>()); }) {
            return std::get<N>(std::forward<TT>(type));
        }
    };

    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        (..., fn(getWay.template operator()<idx>(type)));
    }(std::make_index_sequence<count>{});
};

int main() {
    auto create_entity =                               //
        From::base<Base>                               //
        | With::CureHealth                             //* reorder with priority
        | With::Damage                                 //
        | With::Health                                 //* skipped for Base
        | With::user_property<Damage, extra_token>     //
        | With::user_property<Health, extra_token>     //
        | With::user_property<int, extra_token>        //* similiar with Base::type
        | With::user_property<Data<int, extra_token>>  //* skipped for Base
        ;

    auto entity = create_entity(
        unordered,
        forTags<>(Health{100}),
        forTags<extra_token>(Health{150}),
        forTags<>(Damage{5}),
        forTags<extra_token>(Damage{150}),
        CureHealth{15},  //* can mix with normal types
        forTags<extra_token>(25),
        // Data<int, extra_token>{15}, //! duplication of types if Base - Data is used as way to specify type in C-tor
        forTags<>(Data<int, extra_token>{15}));  //* walkaround - Data<Data<int, extra_token>>

    static_assert(std::same_as<decltype(create_entity)::result_type, decltype(entity)>);

    std::println("type:     {}", name<decltype(entity)>());
    std::println("as_tuple: {}", name<as_tuple<decltype(entity)>>());
    std::println("{}", parse_type_name<decltype(entity)>());

    for_each_type(entity,
                  [](const auto& entry) { std::println("{}", entry); });

    auto tp = to_tuple(entity);
    std::println();
    for_each_type(tp,
                  [](const auto& entry) { std::println("{}", entry); });

    auto [e_dmg, e_hp, e_int] = std::tie(
        getTaged<0, extra_token>(entity),
        getTaged<1, extra_token>(entity),
        getTaged<2, extra_token>(entity));
    std::println();
    std::println("taged:\n  {}\n  {}\n  {}\n", e_dmg, e_hp, e_int);
}
