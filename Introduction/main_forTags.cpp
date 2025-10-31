#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct extra_token {};

struct Base {
    Health hp;
    Data<int, extra_token> type;

    template <size_t DIG>
        requires(DIG < 2)
    decltype(auto) getType(this auto& self) {
        return boost::pfr::get<DIG>(self);
    }
};

template <>
struct UserDefaultValue<Damage, extra_token> {
    static constexpr auto value = [] { return Damage{500}; };
};

template <typename T, typename Tags>
auto& operator<<(std::ostream& out, Data<T, Tags> status) {
    out << status.value;
    return out;
}

template <>
struct std::formatter<Data<int, extra_token>> : std::formatter<std::string> {
    auto format(const Data<int, extra_token>& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << t;
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

template <typename T>
auto to_tuple(T&& type) {
    using TUPLE = as_tuple<std::remove_cvref_t<T>>;
    constexpr size_t count = std::tuple_size_v<TUPLE>;
    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        return TUPLE{type.template getType<idx>()...};
    }(std::make_index_sequence<count>{});
};

template <size_t N, typename T>
decltype(auto) getWay(T&& type) {
    if constexpr (requires { type.template getType<N>(); }) {
        return std::forward<T>(type).template getType<N>();
    } else {
        return std::get<N>(std::forward<T>(type));
    }
}

auto for_each_type = []<typename T, typename Fn>(T&& type, Fn fn) {
    using TUPLE = as_tuple<std::remove_cvref_t<T>>;
    constexpr size_t count = std::tuple_size_v<TUPLE>;

    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        (..., fn(getWay<idx>(type)));
    }(std::make_index_sequence<count>{});
};

int main() {
    auto create_entity =                            //
        From::base<Base>                            //
        | With::Damage                              //
        | With::CureHealth                          //
        | With::Health                              //
        | With::user_property<Damage, extra_token>  //
        | With::user_property<Health, extra_token>  //
        | With::user_property<int, extra_token>     //
        ;

    auto entity = create_entity(unordered,
                                forTags<>(Health{100}),
                                forTags<extra_token>(Health{150}),
                                forTags<>(Damage{5}),  // TODO: mix with normal types
                                forTags<extra_token>(Damage{150}),
                                forTags<>(CureHealth{15}),
                                forTags<extra_token>(25),
                                forTags<>(Data<int, extra_token>{15}));

    std::println("{}", name<decltype(entity)>());

    std::println("{}", parse_type_name<decltype(entity)>());

    for_each_type(entity,
                  [](const auto& entry) { std::println("{}", entry); });

    auto [e_dmg, e_hp, e_int] = std::tie(
        entity.getTaged<0, extra_token>(),
        entity.getTaged<1, extra_token>(),
        entity.getTaged<2, extra_token>());
    std::println("extra:\n\t{}\n\t{}\n\t({})\n", e_dmg, e_hp, e_int);

    using entity_type = decltype(entity);
    std::println("{}", name<as_tuple<entity_type>>());

    auto tp = to_tuple(entity);
    std::println();

    for_each_type(tp,
                  [](const auto& entry) { std::println("{}", entry); });
}
