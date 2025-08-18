// #define NO_PREMADE_PROPERTIES

#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Examples/MainExamples/order_list.hpp"

#include <print>
#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

#include "Taumaturgia/Properties/GeneralFeatures.hpp"

struct y;
struct empty {};

struct Strenght : public impl::UserProperty_<int, empty, y> {};
struct Dexterity : public impl::UserProperty_<float, empty> {};
struct Constitution {};
struct Inteligence {};
struct Wisdom {};
struct Charisma {};

namespace With {
[[maybe_unused]] constexpr auto integer = user_property<int, struct y>;

[[maybe_unused]] constexpr auto Strenght = user_property<::Strenght>;
[[maybe_unused]] constexpr auto Dexterity = user_property<::Dexterity>;
[[maybe_unused]] constexpr auto Constitution = user_property<::Constitution>;
[[maybe_unused]] constexpr auto Inteligence = user_property<::Inteligence>;
[[maybe_unused]] constexpr auto Wisdom = user_property<::Wisdom>;
[[maybe_unused]] constexpr auto Charisma = user_property<::Charisma>;
}  // namespace With

template <typename T>
using Tp = decltype(From::base<T>                           //
                    | With::user_property<float, struct y>  //
                    | With::integer                         //
                    | With::Name                            //
                    | With::Damage                          //
                    | With::Health                          //
                    | With::Protection)::result_type;       //

struct Type {
    // Protection protection;
    // Health hp;

    // template <size_t DIG>
    // decltype(auto) getType(this auto& self) {
    //     if constexpr (DIG == 0)
    //         return self.hp;
    //     if constexpr (DIG == 1)
    //         return self.protection;
    // }
};

int main() {
    using namespace std;

    {
        Tp<Type> tp_type{unordered,
                         Name{"test"},
                         Damage{30, DamageType::Divine},
                         Health{30, 100},
                         13.03f,
                         Protection{ArmorClass{18, BodyLocation::Body}},
                         155};

        auto gt_name = tp_type.getType<Name>();
        auto gt_damage = tp_type.getType<Damage>();
        auto gt_health = tp_type.getType<Health>();
        auto gt_protection = tp_type.getType<Protection>();
        auto gt_int = tp_type.getType<int>();
        auto gt_float = tp_type.getType<float>();

        auto gt_y0 = tp_type.getTaged<0, y>();
        auto gt_y1 = tp_type.getTaged<1, y>();

        std::println("{}: {}", name<decltype(gt_y0)>(), gt_y0);
        std::println("{}: {}", name<decltype(gt_y1)>(), gt_y1);
        std::println();

        auto gt0 = tp_type.getType<0>();
        auto gt1 = tp_type.getType<1>();
        auto gt2 = tp_type.getType<2>();
        auto gt3 = tp_type.getType<3>();
        auto gt4 = tp_type.getType<4>();
        auto gt5 = tp_type.getType<5>();

        std::println("{}: {}", name<decltype(gt_name)>(), gt_name);
        std::println("{}: {}", name<decltype(gt_damage)>(), gt_damage);
        std::println("{}: {}", name<decltype(gt_health)>(), gt_health);
        std::println("{}: {}", name<decltype(gt_protection)>(), gt_protection);
        std::println("{}: {}", name<decltype(gt_int)>(), gt_int);
        std::println("{}: {}", name<decltype(gt_float)>(), gt_float);
        std::println();

        std::println("orders types by order_list:");
        std::println("[{}] {}: {}", 0, name<decltype(gt0)>(), gt0);
        std::println("[{}] {}: {}", 1, name<decltype(gt1)>(), gt1);
        std::println("[{}] {}: {}", 2, name<decltype(gt2)>(), gt2);
        std::println("[{}] {}: {}", 3, name<decltype(gt3)>(), gt3);
        std::println("[{}] {}: {}", 4, name<decltype(gt4)>(), gt4);
        std::println("[{}] {}: {}", 5, name<decltype(gt5)>(), gt5);
        std::println();

        {
            using type = decltype(tp_type);
            auto featured = impl::GeneralFeatures_<type>(tp_type);  // TODO: extract types for getType

            auto gt0 = featured.getType<0>();
            auto gt1 = featured.getType<1>();
            auto gt2 = featured.getType<2>();
            auto gt3 = featured.getType<3>();
            auto gt4 = featured.getType<4>();
            auto gt5 = featured.getType<5>();
            // auto gt6 = featured.getType<6>();

            // cout << "GeneralFeatures_ orders types by reversed order_list :\n"; //! not true
            cout << "[0] " << name<decltype(gt0)>() << ": " << gt0 << '\n';
            cout << "[1] " << name<decltype(gt1)>() << ": " << gt1 << '\n';
            cout << "[2] " << name<decltype(gt2)>() << ": " << gt2 << '\n';
            cout << "[3] " << name<decltype(gt3)>() << ": " << gt3 << '\n';
            cout << "[4] " << name<decltype(gt4)>() << ": " << gt4 << '\n';
            cout << "[5] " << name<decltype(gt5)>() << ": " << gt5 << '\n';
        }

        cout << parse_type_name<decltype(tp_type)>() << '\n';
        cout << name<decltype(tp_type)>() << '\n';
    }

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
