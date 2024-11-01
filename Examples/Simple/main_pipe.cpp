#define IGNORE_ORDER_LIST

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Properties.hpp"

#include "Examples/demangle_type_name.hpp"

#include "Taumaturgia/Properties/Helpers/pipeing.hpp"

// MARK: With

namespace With {
[[maybe_unused]] constexpr Property<Naming> Name{};
[[maybe_unused]] constexpr Property<Damaging> Damage{};
[[maybe_unused]] constexpr Property<Healing> CureHealth{};
[[maybe_unused]] constexpr Property<Living> Health{};
[[maybe_unused]] constexpr Property<Protecting> Protection{};
[[maybe_unused]] constexpr Property<Restoring> EffectTypeContainer{};
[[maybe_unused]] constexpr Property<Wearing> WearContainer{};

template <template <typename> typename P>
[[maybe_unused]] constexpr Property<P> property{};
};  // namespace With

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                                                                                  \
    template <typename... Args>                                                                                               \
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>> \
    ClassName(const Token&, Args&&... args) noexcept {                                                                        \
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);                                     \
    }

// MARK: Base

struct Base {
    Base() noexcept = default;

    Base(int x, int y) noexcept
        : x{x}, y{y} {}

    TokenCtor(Base);

    template <typename T, size_t = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (std::same_as<T, int>) {
            return (type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (type2);
        }
    }
    template <typename T, size_t = 0>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (std::same_as<T, int>) {
            return (type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (type2);
        }
    }

    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};

private:
    int type1{};
    float type2{};
};

// MARK: main

struct Empty {
    auto getFloat(size_t index = 0) { return float_[index % 2]; }
    auto getOtherDamage() { return dmg_; }

    template <typename RETURN, size_t SIZE = 0>
    constexpr decltype(auto) getType(this auto&& self) {
        if constexpr (std::same_as<RETURN, std::string>) {
            return (self.test_);
        } else if constexpr (std::same_as<RETURN, float>) {
            return (self.float_[SIZE % 2]);
        } else {
            return;
        }
    }

private:
    Damage dmg_{50, DamageType::Divine};
    std::array<float, 2> float_{3.1113f, 0.5f};
    std::string test_{"ok"};
};

int main() {
    std::cout << '\n';

    // MARK: print lambda

    auto print = [](auto type) {
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "x      = " << type.x << '\n';
        std::cout << "y      = " << type.y << '\n';
        std::cout << "int    = " << trait<int>::get(type) << '\n';
        std::cout << "float  = " << trait<float>::get(type) << '\n';
        std::cout << "double = " << trait<double>::get(type) << '\n';
        std::cout << '\n';
    };

    // MARK: defaults

    constexpr auto default_x = 12;
    constexpr auto default_y = 5;

    [[maybe_unused]] int default_int{100};
    [[maybe_unused]] float default_float{3.14f};
    [[maybe_unused]] double default_double{20.20};
    [[maybe_unused]] Health default_health{100, 100};
    [[maybe_unused]] Damage default_damage{5, DamageType::Divine};
    [[maybe_unused]] Protection default_protection{10, BodyLocation::Head};
    [[maybe_unused]] Name default_name{"Test"};

    {
        Empty empty{};

        auto create_type =
            empty                                             // ! ignore prototype and use default c-tor
            | With::Damage                                    //
            | With::Name                                      //
            | With::Protection                                //
            | With::Protection                                //
            | With::property<Protecting>                      //
            | With::Health                                    // not in order
            | With::property<UserPropertyAdapter<int>::type>  //
            ;
#ifdef IGNORE_ORDER_LIST
        auto type = create_type(
            Damage{5, DamageType::Physical},
            Name{"Type"},
            Protection{10, BodyLocation::Legs},
            Health{300, 300},  // order as given
            15);
#else
        auto type = create_type(
            Name{"Type"},
            Health{300, 300},  // order as property priority
            Damage{5, DamageType::Physical},
            Protection{10, BodyLocation::Legs},
            15);
#endif
        auto type_temp = create_type(
            unordered,  // order ignored
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical},
            Health{300, 300},
            Name{"Type"});

        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "int        = " << trait<int>::get(type) << '\n';
        std::cout << "float      = " << trait<float>::get(type) << '\n';
        std::cout << "string     = " << trait<std::string>::get(type) << '\n';

        std::cout << "float acces= " << trait<float>::accessable<decltype(type)> << '\n';

        std::cout << "float 0    = " << type.getType<float, 0>() << '\n';
        std::cout << "float 1    = " << type.getType<float, 1>() << '\n';
        std::cout << "string     = " << type.getType<std::string>() << '\n';

        std::cout << "Name       = " << type.getName() << '\n';
        std::cout << "Health     = " << type.getHealth() << '\n';
        std::cout << "Damage     = " << type.getDamage() << '\n';
        std::cout << "Protection = " << type.getProtection() << '\n';
        std::cout << "int        = " << type.getType<int>() << '\n';
        std::cout << "float 0    = " << type.getFloat(0) << '\n';
        std::cout << "float 1    = " << type.getFloat(1) << '\n';
        std::cout << "dmg other  = " << type.getOtherDamage() << '\n';
        std::cout << '\n';

        struct Empty_2 {
            auto getFloat(size_t index = 0) { return f_[index % 2]; }

        private:
            std::array<float, 2> f_{3.1113f, 0.5f};
        };

        Empty_2 empty_2{};

        auto create_type_2 =
            empty_2                                           // ! ignore prototype and use default c-tor
            | With::Damage                                    //
            | With::Name                                      //
            | With::Protection                                //
            | With::Protection                                //
            | With::property<Protecting>                      //
            | With::Health                                    // not in order
            | With::property<UserPropertyAdapter<int>::type>  //
            ;
#ifdef IGNORE_ORDER_LIST
        auto type_2 = create_type_2(
            Damage{5, DamageType::Physical},
            Name{"Type 2"},
            Protection{10, BodyLocation::Legs},
            Health{300, 300},  // order as given
            15);
#else
        auto type_2 = create_type_2(
            Name{"Type 2"},
            Health{300, 300},  // order as property priority
            Damage{5, DamageType::Physical},
            Protection{10, BodyLocation::Legs},
            15);
#endif
        auto type_temp_2 = create_type_2(
            unordered,  // order ignored
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical},
            Health{300, 300},
            Name{"Type 2"});

        std::cout << "type       = " << name<decltype(type_2)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type_2) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type_2) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type_2) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type_2) << '\n';
        std::cout << "int        = " << trait<int>::get(type_2) << '\n';

        std::cout << "float acces= " << trait<float>::accessable<decltype(type_2)> << '\n';

        std::cout << "Name       = " << type_2.getName() << '\n';
        std::cout << "Health     = " << type_2.getHealth() << '\n';
        std::cout << "Damage     = " << type_2.getDamage() << '\n';
        std::cout << "Protection = " << type_2.getProtection() << '\n';
        std::cout << "int        = " << type_2.getType<int>() << '\n';
        std::cout << "float 0    = " << type_2.getFloat(0) << '\n';
        std::cout << "float 1    = " << type_2.getFloat(1) << '\n';

        return 0;
    }

    {  // MARK: create a lambda factory
        Base base{default_x, default_y};

        // create a lambda factory
        auto create_type =
            base                          // ! ignore prototype and use default c-tor
            | With::Name                  //
            | With::Health                //
            | With::Damage                //
            | With::Protection            //
            | With::property<Protecting>  //
            ;

        auto type1 = create_type(
            unordered,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            float{3.14f},  // type<float>
            Protection{10, BodyLocation::Head},
            default_int,    // type<int>
            double{20.20},  // type<double>
            Name{"Test"});

        auto type2 = create_type(
            unordered,  // ignore order of arguments
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name);

        print(type1);
        print(type2);
    }

    {  // MARK: modify target
        auto tlist = With::Name | With::Health | With::Protection | With::Damage;

        auto type3 = Base{default_x, default_y} | tlist;

        Base base{default_x, default_y};  // target
        auto type4 = base | tlist;        // modify existing target type

        // update rest of target parameters
        auto update = [](auto& target) {
            return [&target]<typename... Args>
                requires(
                    (std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>) and  // every argument have unique type
                    (trait<std::remove_cvref_t<Args>>::template accessable<std::remove_cvref_t<decltype(target)>> and ...))             // every type is accessable by trait
            (Args&&... args) {
                ((trait<std::remove_cvref_t<Args>>::get(target) = std::forward<Args>(args)), ...);
            };
        };

        update(type3)(
            Health{100, 100},
            float{3.14f},   // type<float>
            default_int,    // type<int>
            double{20.20},  // type<double>
            Damage{5, DamageType::Magical},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        update(type4)(
            default_int,
            default_float,
            default_double,
            default_health,
            default_damage,
            default_protection,
            default_name);

        print(type3);
        print(type4);
    }

    {                              // MARK: extra example
        list tlist2 = With::Name;  // ? explicit conversion needed (don't use auto)
        auto tlist3 = With::Name;  // ! auto deduce wrong type here (single object is not a list)

        auto tlist4 = tlist2 | With::Health;
        auto tlist5 = tlist3 | With::Health;
        static_assert(std::same_as<decltype(tlist4), decltype(tlist5)>);

        auto type5 = Base{default_x, default_y} | tlist2;
        auto type6 = Base{default_x, default_y} | tlist3;  // ! creator

        std::cout << '\n';
        std::cout << "type5 =    " << name<decltype(type5)>() << '\n';
        std::cout << "type6 =    " << name<decltype(type6)>() << '\n';  // ! creator
        std::cout << '\n';
    }
}
