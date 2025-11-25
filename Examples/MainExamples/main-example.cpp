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
struct empty_next {};
struct other {};

struct Strenght : public impl::UserProperty_<int, empty, struct ignored_y> {};            // ? ignore ignored_y token
struct Strenght_next : public impl::UserProperty_<int, empty_next, struct ignored_y> {};  // ? ignore ignored_y token , empty_next as base
struct Dexterity : public impl::UserProperty_<float, empty> {};
struct Constitution {};
struct Inteligence {};
struct Wisdom {};
struct Charisma {};

struct Attrib {
private:
    using idx = std::tuple<
        Strenght,
        Constitution,
        Charisma,
        int>;

    idx data{};

public:
    template <typename T, size_t = 0, typename Self>
        requires boost::mp11::mp_contains<idx, T>::value
    constexpr decltype(auto) getType(this Self& self) noexcept {
        return std::get<T>(self.data);
    }

    template <size_t S>
        requires(std::tuple_size_v<idx> > S)
    constexpr decltype(auto) getType(this auto& self) noexcept {
        using type = std::remove_cvref_t<decltype(std::get<S>(idx{}))>;
        return trait<type>::get(self);
    }

    template <typename T, size_t = 0>
    constexpr decltype(auto) getType(this auto& self) = delete;
    template <size_t S>
    constexpr decltype(auto) getType(this auto& self) = delete;
};

template <typename T>
concept have_some_getters = requires(T t) {
    t.template getType<Dexterity>();
    t.template getTypeTaged<Strenght, other>();
    t.template getType<0>();
};

namespace With {
[[maybe_unused]] constexpr auto integer = user_property<int, struct y>;

[[maybe_unused]] constexpr auto Strenght = user_property<::Strenght>;
[[maybe_unused]] constexpr auto Strenght2 = user_property<::Strenght, struct other>;
[[maybe_unused]] constexpr auto Strenght2_once = user_property_once<::Strenght, struct other>;
[[maybe_unused]] constexpr auto Strenght_next_other = user_property<::Strenght_next, struct other>;
[[maybe_unused]] constexpr auto Dexterity = user_property<::Dexterity>;
[[maybe_unused]] constexpr auto Constitution = user_property<::Constitution>;
[[maybe_unused]] constexpr auto Inteligence = user_property<::Inteligence>;
[[maybe_unused]] constexpr auto Wisdom = user_property<::Wisdom>;
[[maybe_unused]] constexpr auto Charisma = user_property<::Charisma>;
}  // namespace With

template <typename T>
using T_7attrib = decltype(From::base<T>         //
                    | With::Strenght      //
                    | With::Strenght2     //
                    | With::Dexterity     //
                    | With::Constitution  //
                    | With::Inteligence   //
                    | With::Wisdom        //
                    | With::Charisma      //
                    )::result_type;       //

int main() {
    using namespace std;

    auto print_get_by_type = [](have_some_getters auto& type) {
        auto gt0_ = type.template getType<Dexterity>();
        auto gt1_ = type.template getType<Strenght>();
        auto gt2_ = type.template getType<Constitution>();
        auto gt3_ = type.template getType<Inteligence>();
        auto gt4_ = type.template getType<Wisdom>();
        auto gt5_ = type.template getType<Charisma>();
        auto gt6_ = type.template getTypeTaged<Strenght, other>();
        auto gt7_ = type.template getType<int>();

        std::println("[] {} {}", name<decltype(gt0_)>(), gt0_.getType());
        std::println("[] {} {}", name<decltype(gt1_)>(), gt1_.getType());
        std::println("[] {}", name<decltype(gt2_)>());
        std::println("[] {}", name<decltype(gt3_)>());
        std::println("[] {}", name<decltype(gt4_)>());
        std::println("[] {}", name<decltype(gt5_)>());

        std::println("[] {}", name<decltype(gt6_)>());
        std::println("[] {}", name<decltype(gt7_)>());
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

        std::println("[0] {}", name<decltype(gt0)>());
        std::println("[1] {}", name<decltype(gt1)>());
        std::println("[2] {}", name<decltype(gt2)>());
        std::println("[3] {}", name<decltype(gt3)>());
        std::println("[4] {}", name<decltype(gt4)>());
        std::println("[5] {}", name<decltype(gt5)>());
        std::println("[6] {}", name<decltype(gt6)>());
        std::println("[7] {}", name<decltype(gt7)>());
    };

    {
        cout << "[Strenght::improvement_of]"
             << parse_type_name<Strenght::improvement_of>()
             << '\n';
        cout << "[Strenght_next::improvement_of]"
             << parse_type_name<Strenght_next::improvement_of>()
             << '\n';
    }
    {
        cout << "[Attrib]"
             << parse_type_name<Attrib>()
             << '\n';
    }
    {
        cout << "[T_7attrib<Attrib>]"
             << parse_type_name<T_7attrib<Attrib>>()
             << '\n';
    }
    {
        using Attrib_updated = impl::UserProperty_<Strenght, Attrib, other>;                                   // ? introduce <Strenght, other>
        using Attrib_updated2 = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght, other>::apply>;   // ? introduce <Strenght, other>
        using Attrib_updated3 = decltype(From::base<Attrib> | With::Strenght2 | With::Strenght)::result_type;  // ? introduce <Strenght, other>
        using Attrib_updated3b = decltype(Attrib{} | With::Strenght2 | With::Strenght | Create);               // ? introduce <Strenght, other>

        static_assert(std::same_as<Attrib_updated, Attrib_updated2>);
        static_assert(std::same_as<Attrib_updated, Attrib_updated3>);
        static_assert(std::same_as<Attrib_updated, Attrib_updated3b>);

        using Attrib_updated4 = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght, other>::once>;  // * not introduce <Strenght, other>
        using Attrib_updated5 = decltype(From::base<Attrib> | With::Strenght2_once)::result_type;            // * not introduce <Strenght, other>

        static_assert(std::same_as<Attrib_updated4, Attrib_updated5>);

        {
            // if base of Strenght is diffrent
            using Attrib_updated_a = add_properties_ordered<Attrib, UserPropertyAdapter<Strenght_next, other>::apply>;  // ? introduce <Strenght_next, other>
            using Attrib_updated_b = decltype(From::base<Attrib> | With::Strenght_next_other)::result_type;             // ? introduce <Strenght_next, other>

            static_assert(std::same_as<Attrib_updated_a, Attrib_updated_b>);
        }

        cout << "[Attrib_updated]"
             << parse_type_name<Attrib_updated>()
             << '\n';
        cout << "[Attrib_updated3]"
             << parse_type_name<Attrib_updated3>()
             << '\n';
        cout << "[T_7attrib<Attrib_updated>]"
             << parse_type_name<T_7attrib<Attrib_updated>>()
             << '\n';

        T_7attrib<Attrib_updated> type{};

        type.getType<Strenght>() = {15};
        type.getType<Dexterity>() = {18.1f};

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
