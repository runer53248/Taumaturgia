#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct extra_token {};
using extra_tag = Tags<extra_token>;

template <typename T, size_t N>
concept get_limited = N < boost::pfr::tuple_size_v<std::remove_cvref_t<T>>;

struct Base {
    Health hp;
    // Damage dmg;
    Data<int, extra_tag> type{};

    template <size_t DIG, get_limited<DIG> Self>
    decltype(auto) getType(this Self& self) {
        return boost::pfr::get<DIG>(self);
    }
};

// MARK: UserDefaultValue

template <>
struct UserDefaultValue<Damage, extra_tag> {
    static constexpr auto value = [] { return Damage{500}; };
};

// MARK: operator<<

template <typename T, isTag TAGS = no_tag>
auto& operator<<(std::ostream& out, Data<T, TAGS> status) {
    out << status.value;
    return out;
}

// MARK: std::formatter

template <>
struct std::formatter<Data<int, extra_tag>> : std::formatter<std::string> {
    auto format(const Data<int, extra_tag>& t, [[maybe_unused]] std::format_context& ctx) const {
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

//

template <auto GET>
using for_each_impl = decltype([]<typename T, typename Fn>(T&& type, Fn fn) {
    constexpr size_t count = std::tuple_size_v<as_tuple<std::remove_cvref_t<T>>>;

    return [&]<size_t... idx>(std::index_sequence<idx...>) {
        (..., fn(GET.template operator()<idx>(std::forward<T>(type))));
    }(std::make_index_sequence<count>{});
});

auto for_template = for_each_impl<[]<size_t N, typename T>(T&& t) {
    if constexpr (requires { std::get<N>(std::declval<T>()); }) {
        return std::get<N>(std::forward<T>(t));
    } else if constexpr (requires { getType<N>(std::declval<T>()); }) {
        return getType<N>(std::forward<T>(t));
    }
}>{};

int main() {
    auto create_entity =                                     //
        From::base<Base>                                     //
        | With::CureHealth                                   //* reorder with priority
        | With::Damage                                       //
        | With::Health                                       //* skipped for Base
        | With::user_property<Damage, extra_tag>     //
        | With::user_property<Health, extra_tag>     //
        | With::user_property<int, extra_tag>        //* similiar with Base::type
        | With::user_property<Data<int, extra_tag>>  //* skipped for Base
        ;

    auto entity = create_entity(unordered,
                                forTags<>(Damage{5}),
                                forTags<>(Health{5}),
                                forTags<>(CureHealth{5}),
                                forTags<>(Data<int, extra_tag>{5}),
                                forTags<extra_tag>(Damage{50}),
                                forTags<extra_tag>(Health{50}),
                                forTags<extra_tag>(int{50})
                                //
    );

    auto print = [](const auto& entry) { std::println("{:40}{}", name<decltype(entry)>(), entry); };

    std::println("{}{}{}\n", Color::Grey, name<decltype(entity)>(), Color::Reset);
    for_template(entity, print);
    std::println();

    auto tp = to_tuple(entity);
    std::println("{}{}{}\n", Color::Grey, name<decltype(tp)>(), Color::Reset);
    for_template(tp, print);
    std::println();
}
