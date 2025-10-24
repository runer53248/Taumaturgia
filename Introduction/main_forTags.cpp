#include <boost/pfr.hpp>
#include <print>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct extra_token {};

struct Base {
    Health hp;
    Data<int, extra_token> type;

    template <size_t DIG>
    decltype(auto) getType(this auto& self) {
        return boost::pfr::get<DIG>(self);
    }
};

template <typename T, typename Tags>
auto& operator<<(std::ostream& out, Data<T, Tags> status) {
    out << status.value;
    return out;
}

template <preety_printed<Data<int, extra_token>> T>
struct std::formatter<T> : std::formatter<std::string> {
    auto format(const T& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << t;
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

template <>
struct UserDefaultValue<Damage, extra_token> {
    static constexpr auto value = [] { return Damage{500}; };
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

    std::vector entities{
        create_entity(unordered,
                      forTags<>(Health{100}),
                      forTags<extra_token>(Health{150}),
                      forTags<>(Damage{5}),  // TODO: mix with normal types
                      forTags<extra_token>(Damage{150}),
                      forTags<>(CureHealth{15}),
                      forTags<extra_token>(25),
                      forTags<>(Data<int, extra_token>{15}))};

    std::println("{}", parse_type_name<decltype(create_entity)::result_type, Data<int, extra_token>>());

    for (auto entity : entities) {
        [&]<size_t... idx>(std::index_sequence<idx...>) {
            (..., std::println("{}", entity.template getType<idx>()));
            std::cout << '\n';
        }(std::make_index_sequence<7>{});

        auto [e_dmg, e_hp, e_int] = std::tie(
            entity.getTaged<0, extra_token>(),
            entity.getTaged<1, extra_token>(),
            entity.getTaged<2, extra_token>());
        std::println("extra: {} {} ({})\n", e_dmg, e_hp, e_int);
    }
}
