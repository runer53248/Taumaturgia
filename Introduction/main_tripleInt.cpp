#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct extra_token {};

struct BaseTripleInt {
    int x;
    int y;
    int z;

    template <size_t DIG, typename Self>
        requires(DIG < boost::pfr::tuple_size_v<Self>)
    decltype(auto) getType(this Self& self) {
        return boost::pfr::get<DIG>(self);
    }
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
    auto create_double =
        From::base<BaseTripleInt>  //
        | With::Health             //
        | With::Damage             //
        ;

    auto entity = create_double(Health{5, 10}, Damage{15}, 1, 2, 3);

    std::println("{}", parse_type_name<decltype(entity)>());
    for_each_type(entity,
                  [](const auto& entry) { std::println("{:8} : {}", name<std::remove_cvref_t<decltype(entry)>>(), entry); });
}
