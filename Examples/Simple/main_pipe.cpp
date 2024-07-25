// #define IGNORE_ORDER_LIST

// TODO: split preety prints requiring Object class from those that don't and group them for simple one include
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/PreetyPrint/PrintHealth.hpp"
#include "Examples/PreetyPrint/PrintName.hpp"
#include "Examples/PreetyPrint/PrintProtection.hpp"
#include "Usage/Strategies.hpp"

#include "Examples/demangle_type_name.hpp"

#include <functional>

namespace With {
[[maybe_unused]] constexpr Property<Naming> Name{};
[[maybe_unused]] constexpr Property<Damaging> Damage{};
[[maybe_unused]] constexpr Property<Healing> CureHealth{};
[[maybe_unused]] constexpr Property<Living> Health{};
[[maybe_unused]] constexpr Property<Protecting> Protection{};
[[maybe_unused]] constexpr Property<Restoring> EffectTypeContainer{};
[[maybe_unused]] constexpr Property<Wearing> WearContainer{};
};  // namespace With

template <typename T, template <typename> typename Prop>
auto operator|(T, Property<Prop>) {
    return []<typename Arg, typename... Args>(Arg&& arg, Args&&... args) {
        constexpr bool inv_first_arg = std::invocable<T, Arg>;
        constexpr bool token_same = std::is_same_v<std::remove_cvref_t<Arg>, Token>;

        if constexpr (inv_first_arg) {
            using type = std::invoke_result_t<T, Arg>;
            using result_property = add_properties<type, Prop>;

            if constexpr (not token_same) {  // token not introduced
                static_assert(std::constructible_from<result_property, Arg, Args...>);
                return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else {                                                                     // token was introduced
                if constexpr (std::constructible_from<result_property, Arg, Args...>) {  // can be constructed
                    static_assert(std::constructible_from<result_property, Arg, Args...>);
                    return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
                } else if constexpr (std::constructible_from<result_property, Args...>) {  // ignore token Arg
                    static_assert(std::constructible_from<result_property, Args...>);
                    return result_property(std::forward<Args>(args)...);
                } else {  // T is base type (propably) and token was introduced - meaning unknown order of arguments given
                    auto result = result_property{};
                    ((trait<Args>::get(result) = std::forward<Args>(args)), ...);
                    return result;
                }
            }
        } else if constexpr (token_same) {  // token was introduced
            using type = T;
            using result_property = add_properties<type, Prop>;

            if constexpr (std::constructible_from<result_property, Arg, Args...>) {
                static_assert(std::constructible_from<result_property, Arg, Args...>);
                return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
            } else {  // ignore Arg == Token
                static_assert(std::constructible_from<result_property, Args...>);
                return result_property(std::forward<Args>(args)...);
            }
        } else {  // token not introduced
            using type = T;
            using result_property = add_properties<type, Prop>;

            static_assert(std::constructible_from<result_property, Arg, Args...>);
            return result_property(std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    };
}

template <template <typename...> typename Prop1, template <typename...> typename Prop2>
auto operator|(Property<Prop1>, Property<Prop2>) {
    return taged_list<Prop1, Prop2>{};
}

template <typename... Props, template <typename> typename Prop2>
auto operator|(list<Props...>, Property<Prop2>) {
    return boost::mp11::mp_append<list<Props...>, taged_list<Prop2>>{};
}

// for build in properties

template <typename T, template <typename> typename... Props, typename P>
auto fx(T, Props<P>...) {
    using result = add_properties<T, Props...>;
    return result{};
}

// for user type properties

template <typename T, template <typename, typename> typename... Props, typename... TYPES, typename P>
auto fx(T, Props<TYPES, P>...) {
    using result = add_properties<T, UserPropertyAdapter<TYPES>::template type...>;
    return result{};
}

//

template <typename T, typename... Props>
auto operator|(T, list<Props...>) {
    return fx(T{}, Props{}...);
}

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

#define TokenCtor(ClassName)                                         \
    template <type_of<Token> Arg, typename... Args>                  \
    ClassName(Arg&, Args&&... args) noexcept {                       \
        ((trait<Args>::get(*this) = std::forward<Args>(args)), ...); \
    }

struct Base {
    int x;
    // Name name;
    // Damage dmg;
    // Health hp;
    // Protection protection;

    Base() noexcept = default;

    Base(int x)
        : x{x} {}

    // template <type_of<Token> Arg, typename... Args>
    // Base(Arg&, Args&&... args) noexcept {
    //     ((trait<Args>::get(*this) = std::forward<Args>(args)), ...);
    // }

    TokenCtor(Base)
};

int main() {
    std::cout << '\n';
    {
        // create a type
        using type_1 = add_properties<
            Base,
            Living,
            Damaging,
            Protecting,
            Naming>;

        auto t1 = type_1{
            token,  // ignore order of arguments
            Damage{5, DamageType::Divine},
            Health{100, 100},
            Protection{10, BodyLocation::Head},
            Name{"Test"},
        };

        std::cout << name<decltype(t1)>() << '\n';
        std::cout << trait<Name>::get(t1) << '\n';
        std::cout << trait<Damage>::get(t1) << '\n';
        std::cout << trait<Protection>::get(t1) << '\n';
        std::cout << trait<Health>::get(t1) << '\n';
        std::cout << '\n';
    }

    {
        // create a properties_list
        using p_list = properties_list<
            Living,
            Damaging,
            Protecting,
            Naming>;

        // create a type
        using type_1 = p_list::apply_properties<Base>;

        auto t1 = type_1{
            token,  // ignore order of arguments
            Damage{5, DamageType::Divine},
            Health{100, 100},
            Protection{10, BodyLocation::Head},
            Name{"Test"},
        };

        std::cout << name<decltype(t1)>() << '\n';
        std::cout << trait<Name>::get(t1) << '\n';
        std::cout << trait<Damage>::get(t1) << '\n';
        std::cout << trait<Protection>::get(t1) << '\n';
        std::cout << trait<Health>::get(t1) << '\n';
        std::cout << '\n';
    }

    {
        // create a lambda factory
        auto create_type_2 =
            Base{}              //
            | With::Name        //
            | With::Health      //
            | With::Damage      //
            | With::Protection  //
            ;

        auto t2 = create_type_2(
            token,  // ignore order of arguments
            Health{100, 100},
            Damage{5, DamageType::Magical},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        std::cout << name<decltype(t2)>() << '\n';
        std::cout << trait<Name>::get(t2) << '\n';
        std::cout << trait<Damage>::get(t2) << '\n';
        std::cout << trait<Protection>::get(t2) << '\n';
        std::cout << trait<Health>::get(t2) << '\n';

        // std::cout << traits::accessType<Name>::get(t2) << '\n';
        // std::cout << traits::accessType<Damage>::get(t2) << '\n';
        // std::cout << traits::accessType<Protection>::get(t2) << '\n';
        // std::cout << traits::accessType<Health>::get(t2) << '\n';

        std::cout << '\n';
    }

    {
        auto tlist = With::Name | With::Health | With::Protection | With::Damage;

        Base base{12};

        // modify existing object
        auto tp = base | tlist;

        std::cout << base.x << '\n';
        std::cout << tp.x << '\n';  // ! should remember x value
        std::cout << "tlist =  " << name<decltype(tlist)>() << '\n';
        std::cout << "tp =     " << name<decltype(tp)>() << '\n';
        std::cout << '\n';

        [&]<typename... Args>(Args&&... args) {
            ((trait<Args>::get(tp) = std::forward<Args>(args)), ...);
        }(
            Health{100, 100},
            Damage{5},
            Protection{10, BodyLocation::Head},
            Name{"Test"});

        std::cout << name<decltype(tp)>() << '\n';
        std::cout << trait<Name>::get(tp) << '\n';
        std::cout << trait<Damage>::get(tp) << '\n';
        std::cout << trait<Protection>::get(tp) << '\n';
        std::cout << trait<Health>::get(tp) << '\n';
    }
}
