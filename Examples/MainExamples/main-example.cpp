#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Examples/MainExamples/order_list.hpp"

#include <print>
#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

#include "Taumaturgia/Properties/GeneralFeatures.hpp"

struct ignored_y;
struct empty {};
struct other {};

using tag_ignored_y = Tags<struct ignored_y>;

template <auto T>
using as_type = decltype(T)::result_type;

using strenght_base = as_type<From::base<empty>                          //
                              | With::user_property<int, tag_ignored_y>  //
                              | With::user_property<int>>;
struct Strenght : public strenght_base {
    using strenght_base::strenght_base;
};  //

using strenght_next_base = as_type<From::base<empty>                          //
                                   | With::user_property<int, tag_ignored_y>  //
                                   | With::user_property<int>                 //
                                   | With::user_property<Strenght>>;
struct Strenght_next : public strenght_next_base {
    using strenght_next_base::strenght_next_base;
};  //

struct Dexterity : public impl::UserProperty_<float, empty> {};
struct Constitution : public impl::UserProperty_<int, empty> {};
struct Inteligence : public impl::UserProperty_<int, empty> {};
struct Wisdom : public impl::UserProperty_<int, empty> {};
struct Charisma : public impl::UserProperty_<int, empty> {};

template <preety_printed<Strenght> T>
struct std::formatter<T> : std::formatter<std::string> {
    auto format(const T& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << "["
          << t.template getType<0>()
          << ", "
          << t.template getType<1>()
          << "]";
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

template <preety_printed<Strenght_next> T>
struct std::formatter<T> : std::formatter<std::string> {
    auto format(const T& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << "["
          << t.template getType<0>()
          << ", "
          << t.template getType<1>()
          << ", "
          << std::format("{}", t.template getType<2>())
          << "]";
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

template <preety_printed<Dexterity, Constitution, Inteligence, Wisdom, Charisma> T>
struct std::formatter<T> : std::formatter<std::string> {
    auto format(const T& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << "[" << t.template getType<0>() << "]";
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

struct Attrib {
private:
    using idx = std::tuple<
        Strenght,
        Constitution,
        Charisma,
        int>;

    idx data{};

public:
    template <typename T, size_t S = 0, typename Self>
        requires(boost::mp11::mp_contains<idx, T>::value and S == 0)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        return std::get<T>(self.data);
    }

    template <size_t S>
        requires(std::tuple_size_v<idx> > S)
    constexpr decltype(auto) getType(this auto& self) noexcept {
        using type = std::remove_cvref_t<decltype(std::get<S>(idx{}))>;
        return trait<type>::get(self);
    }

    template <typename T, size_t S = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) = delete;
    template <size_t S>
    constexpr decltype(auto) getType(this auto& self) = delete;
};

using tag_y = Tags<struct y>;
using tag_other = Tags<struct other>;

template <typename T>
concept have_some_getters = requires(T t) {
    t.template getType<Dexterity>();
    t.template getTypeTaged<Strenght, tag_other>();
    t.template getType<0>();
};

namespace With {
[[maybe_unused]] constexpr auto integer = user_property<int, tag_y>;

[[maybe_unused]] constexpr auto Strenght = user_property<::Strenght>;
[[maybe_unused]] constexpr auto Strenght2 = user_property<::Strenght, tag_other>;
[[maybe_unused]] constexpr auto Strenght_next_other = user_property<::Strenght_next, tag_other>;
[[maybe_unused]] constexpr auto Dexterity = user_property<::Dexterity>;
[[maybe_unused]] constexpr auto Constitution = user_property<::Constitution>;
[[maybe_unused]] constexpr auto Inteligence = user_property<::Inteligence>;
[[maybe_unused]] constexpr auto Wisdom = user_property<::Wisdom>;
[[maybe_unused]] constexpr auto Charisma = user_property<::Charisma>;
}  // namespace With

template <typename T>
using T_7attrib = decltype(From::base<T>                //
                           | With::Strenght             //
                           | With::Strenght2            //
                           | With::Strenght_next_other  //
                           | With::Dexterity            //
                           | With::Constitution         //
                           | With::Inteligence          //
                           | With::Wisdom               //
                           | With::Charisma             //
                           )::result_type;              //

int main() {
    using namespace std;

    {
        std::println("[Strenght::improvement_of]{}", parse_type_name<Strenght_next::improvement_of>());
        std::println("[Strenght_next::improvement_of]{}", parse_type_name<Strenght::improvement_of>());
        std::println("[Attrib]{}", parse_type_name<Attrib>());
        std::println("[T_7attrib<Attrib>]{}", parse_type_name<T_7attrib<Attrib>>());
    }
    {
        using Attrib_updated = impl::UserProperty_<Strenght, Attrib, tag_other>;  // ? introduce <Strenght, other>

        {
            using Attrib_updated2 = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght, tag_other>::apply>;  // ? introduce <Strenght, other>
            using Attrib_updated3 = decltype(From::base<Attrib> | With::Strenght2 | With::Strenght)::result_type;     // ? introduce <Strenght, other>
            using Attrib_updated3b = decltype(Attrib{} | With::Strenght2 | With::Strenght | Create);                  // ? introduce <Strenght, other>

            static_assert(std::same_as<Attrib_updated, Attrib_updated2>);
            static_assert(std::same_as<Attrib_updated, Attrib_updated3>);
            static_assert(std::same_as<Attrib_updated, Attrib_updated3b>);
        }
        {
            using Attrib_updated4 = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght, tag_other>::once>;               // * not introduce <Strenght, tag_other>
            using Attrib_updated5 = decltype(From::base<Attrib> | With::user_property_once<::Strenght, tag_other>)::result_type;  // * not introduce <Strenght, tag_other>

            static_assert(std::same_as<Attrib_updated4, Attrib_updated5>);
        }
        {
            // if base of Strenght is diffrent
            using Attrib_updated_a = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght_next, tag_other>::apply>;  // ? introduce <Strenght_next, tag_other>
            using Attrib_updated_b = decltype(From::base<Attrib> | With::Strenght_next_other)::result_type;                 // ? introduce <Strenght_next, tag_other>

            static_assert(std::same_as<Attrib_updated_a, Attrib_updated_b>);
        }

        std::println("[Attrib_updated]{}", parse_type_name<Attrib_updated>());
        std::println("[T_7attrib<Attrib_updated>]{}", parse_type_name<T_7attrib<Attrib_updated>>());

        T_7attrib<Attrib_updated> type{};

        getTypeTaged<Strenght>(type) = Strenght{unordered,
                                                forTags<tag_ignored_y>(105),
                                                forTags<>(15)};  //? Attrib class don't have getTypeTaged for own data
        type.getTypeTaged<Strenght, tag_other>() = {25, 1};
        type.getTypeTaged<Strenght_next, tag_other>() = Strenght_next{unordered,
                                                                      forTags<tag_ignored_y>(8),
                                                                      forTags<>(9),
                                                                      forTags<no_tag, Strenght>({11, 12})};
        type.getType<Dexterity>() = {18.1f};
        type.getType<Constitution>() = {10};
        type.getType<Inteligence>() = {13};
        type.getType<Wisdom>() = {16};
        type.getType<Charisma>() = {8};
        type.getType<int>() = {199};

        auto print_get_by_type = [](have_some_getters auto& type) {
            auto gt0_ = type.template getType<Strenght, 0>();
            auto gt1_ = type.template getType<Strenght, 1>();
            // auto gt2__ = type.template getType<Strenght, 2>(); // deleted
            auto gt2_ = type.template getType<Strenght_next>();
            auto gt3_ = type.template getType<Dexterity>();
            auto gt4_ = type.template getType<Constitution>();
            auto gt5_ = type.template getType<Inteligence>();
            auto gt6_ = type.template getType<Wisdom>();
            auto gt7_ = type.template getType<Charisma>();
            auto gt8_ = type.template getType<int>();

            std::println("[] {:15} {:5}", name<decltype(gt0_)>(), gt0_);
            std::println("[] {:15} {:5}", name<decltype(gt1_)>(), gt1_);
            std::println("[] {:15} {:5}", name<decltype(gt2_)>(), gt2_);
            std::println("[] {:15} {:5}", name<decltype(gt3_)>(), gt3_);
            std::println("[] {:15} {:5}", name<decltype(gt4_)>(), gt4_);
            std::println("[] {:15} {:5}", name<decltype(gt5_)>(), gt5_);
            std::println("[] {:15} {:5}", name<decltype(gt6_)>(), gt6_);
            std::println("[] {:15} {:5}", name<decltype(gt7_)>(), gt7_);
            std::println("[] {:15} {:5}", name<decltype(gt8_)>(), gt8_);
            std::println();
        };

        auto print_get_by_index = [](have_some_getters auto& type) {
            auto gt0 = type.template getType<0>();
            auto gt1 = type.template getType<1>();
            auto gt2 = type.template getType<2>();
            auto gt3 = type.template getType<3>();
            auto gt4 = type.template getType<4>();
            auto gt5 = type.template getType<5>();
            auto gt6 = type.template getType<6>();
            auto gt7 = type.template getType<7>();
            auto gt8 = type.template getType<8>();

            std::println("[0] {:15} {:5}", name<decltype(gt0)>(), gt0);
            std::println("[1] {:15} {:5}", name<decltype(gt1)>(), gt1);
            std::println("[2] {:15} {:5}", name<decltype(gt2)>(), gt2);
            std::println("[3] {:15} {:5}", name<decltype(gt3)>(), gt3);
            std::println("[4] {:15} {:5}", name<decltype(gt4)>(), gt4);
            std::println("[5] {:15} {:5}", name<decltype(gt5)>(), gt5);
            std::println("[6] {:15} {:5}", name<decltype(gt6)>(), gt6);
            std::println("[7] {:15} {:5}", name<decltype(gt7)>(), gt7);
            std::println("[8] {:15} {:5}", name<decltype(gt8)>(), gt8);
        };

        print_get_by_type(type);
        print_get_by_index(type);

        // type.getType<8>();                    //? call of deleted function
        // type.getType<long>();                 //? call of deleted function
        // type.getTypeTaged<Strenght, long>();  //? call of deleted function
    }

    {
#ifdef USES_ADD_PROPERTIES
        check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
