// #define NO_PREMADE_PROPERTIES

#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Examples/MainExamples/order_list.hpp"

#include <print>

#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

#include "Taumaturgia/Properties/GeneralFeatures.hpp"

struct y;
struct empty {};
struct other {};

struct Strenght : public impl::UserProperty_<int, empty, struct y> {};  // ? ignore sub tokens
struct Dexterity : public impl::UserProperty_<float, empty> {};
struct Constitution {};
struct Inteligence {};
struct Wisdom {};
struct Charisma {};

namespace With {
[[maybe_unused]] constexpr auto integer = user_property<int, struct y>;

[[maybe_unused]] constexpr auto Strenght = user_property<::Strenght>;
[[maybe_unused]] constexpr auto Strenght2 = user_property<::Strenght, struct other>;
[[maybe_unused]] constexpr auto Dexterity = user_property<::Dexterity>;
[[maybe_unused]] constexpr auto Constitution = user_property<::Constitution>;
[[maybe_unused]] constexpr auto Inteligence = user_property<::Inteligence>;
[[maybe_unused]] constexpr auto Wisdom = user_property<::Wisdom>;
[[maybe_unused]] constexpr auto Charisma = user_property<::Charisma>;
}  // namespace With

template <typename T>
using Ta = decltype(From::base<T>         //
                    | With::Strenght      //
                    | With::Strenght2     //
                    | With::Dexterity     //
                    | With::Constitution  //
                    | With::Inteligence   //
                    | With::Wisdom        //
                    | With::Charisma      //
                    )::result_type;       //

struct Attrib_ {
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

using Attrib = impl::UserProperty_<Strenght, Attrib_, other>; // ? forced version

int main() {
    using namespace std;

    Ta<Attrib> type{};
    type.getType<Strenght>() = {15};
    type.getType<Dexterity>() = {18.1f};

    {
        auto gt0_ = type.getType<Dexterity>();
        auto gt1_ = type.getType<Strenght>();
        auto gt2_ = type.getType<Constitution>();
        auto gt3_ = type.getType<Inteligence>();
        auto gt4_ = type.getType<Wisdom>();
        auto gt5_ = type.getType<Charisma>();
        
        auto gt6_ = type.getTypeTaged<Strenght, other>();
        auto gt7_ = type.getType<int>();

        std::println("[] {} {}", name<decltype(gt0_)>(), gt0_.getType());
        std::println("[] {} {}", name<decltype(gt1_)>(), gt1_.getType());
        std::println("[] {}", name<decltype(gt2_)>());
        std::println("[] {}", name<decltype(gt3_)>());
        std::println("[] {}", name<decltype(gt4_)>());
        std::println("[] {}", name<decltype(gt5_)>());

        std::println("[] {}", name<decltype(gt6_)>());
        std::println("[] {}", name<decltype(gt7_)>());
        std::println();
    }

    {
        auto gt0 = type.getType<0>();
        auto gt1 = type.getType<1>();
        auto gt2 = type.getType<2>();
        auto gt3 = type.getType<3>();
        auto gt4 = type.getType<4>();
        auto gt5 = type.getType<5>();
        auto gt6 = type.getType<6>();
        auto gt7 = type.getType<7>();

        std::println("[0] {}", name<decltype(gt0)>());
        std::println("[1] {}", name<decltype(gt1)>());
        std::println("[2] {}", name<decltype(gt2)>());
        std::println("[3] {}", name<decltype(gt3)>());
        std::println("[4] {}", name<decltype(gt4)>());
        std::println("[5] {}", name<decltype(gt5)>());
        std::println("[6] {}", name<decltype(gt6)>());
        std::println("[7] {}", name<decltype(gt7)>());
    }

    cout << parse_type_name<decltype(type),
                            Strenght,
                            Dexterity,
                            Constitution,
                            Inteligence,
                            Wisdom,
                            Charisma>()
         << '\n';
}
