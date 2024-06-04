#include "Taumaturgia/Properties/Helpers/taged_list.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"
#include "Taumaturgia/Traits/NameTraits.hpp"

#ifdef NO_PREMADE_PROPERTIES
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Taumaturgia/Types/Health.hpp"
#include "Taumaturgia/Types/Name.hpp"

template <typename TYPE>
using Living = UserPropertyConceptAdapter<Health, Livingable<TYPE>>::template type<TYPE>;

template <typename TYPE>
using Naming = UserPropertyConceptAdapter<Name, Namingable<TYPE>>::template type<TYPE>;

template <typename TYPE>
using Integering = UserPropertyAdapter<int>::template type<TYPE>;

template <typename T>
using Living_impl = impl::UserProperty_<Health, T>;
#else
#include "Taumaturgia/Properties/Premade/Living.hpp"
#include "Taumaturgia/Properties/Premade/Naming.hpp"

template <typename T>
using Living_impl = impl::Living_<T>;
#endif

#include "Taumaturgia/Properties/UserProperty.hpp"
template <typename TYPE>
using Integering = UserPropertyAdapter<int>::template type<TYPE>;

using order_list = taged_list<
    Integering,
    Living,
    Naming  // should be last property to add (used closest to type)
    >;
#include "Taumaturgia/Properties/Helpers/Property.hpp"

///////////////////////////////////////////

namespace impl {
constexpr const char new_living_type_name[] = "NewLiving";

template <typename T>
struct LivingImproved_1_ : public T {
    using property_data = PropertyData<new_living_type_name, LivingImproved_1_, T>;
    using improvement_of = Living_impl<T>;

    LivingImproved_1_() noexcept = default;

    template <std::same_as<Health> HEALTH, typename... Args>
    LivingImproved_1_(const Name& name, HEALTH&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp{std::forward<HEALTH>(hp)} {}

    Health hp;
};

template <typename T, typename... Tags>
struct LivingImproved_2_ : public T {
    using property_data = PropertyData<new_living_type_name, LivingImproved_2_, T, Tags...>;
    using improvement_of = Living_impl<T>;

    LivingImproved_2_() noexcept = default;

    template <std::same_as<Health> HEALTH, typename... Args>
    LivingImproved_2_(const Name& name, HEALTH&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::forward<HEALTH>(hp)} {}

    constexpr decltype(auto) getHealth(this auto& self) {
        return (self.hp_);
    }

private:
    Health hp_{};
};

template <typename T>
struct Improved_LivingImproved_3_ : public T {
    using property_data = PropertyData<new_living_type_name, Improved_LivingImproved_3_, T>;
    using improvement_of = LivingImproved_2_<T>;

    Improved_LivingImproved_3_() noexcept = default;

    template <std::same_as<Health> HEALTH, typename... Args>
    Improved_LivingImproved_3_(const Name& name, HEALTH&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::forward<HEALTH>(hp)} {}

    constexpr auto& getHealth(this auto& self) {
        return self.hp_;
    }

private:
    Health hp_{};
};

template <typename T>
struct Improved_LivingImproved_4_ : public T {
    using property_data = PropertyData<new_living_type_name, Improved_LivingImproved_4_, T>;
    using improvement_of = Improved_LivingImproved_3_<T>;

    Improved_LivingImproved_4_() noexcept = default;

    template <std::same_as<Health> HEALTH, typename... Args>
    Improved_LivingImproved_4_(const Name& name, HEALTH&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::forward<HEALTH>(hp)} {}

    constexpr auto& getHealth(this auto& self) {
        return self.hp_;
    }

private:
    Health hp_{};
};

template <typename T>
struct Improved_ : public T {
    using property_data = PropertyData<new_living_type_name, Improved_, T>;
    using improvement_of = void;

    Improved_() noexcept = default;

    template <std::same_as<Health> HEALTH, typename... Args>
    Improved_(const Name& name, HEALTH&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::forward<HEALTH>(hp)} {}

    constexpr auto& getHealth(this auto& self) {
        return self.hp_;
    }

private:
    Health hp_{};
};
}  // namespace impl

template <typename T>
using Living_1_Improved = std::conditional_t<Livingable<T>, T, impl::LivingImproved_1_<T>>;

template <typename T>
using Living_2_Improved = std::conditional_t<Livingable<T>, T, impl::LivingImproved_2_<T>>;

template <typename T>
using Improved_Living_3_Improved = std::conditional_t<Livingable<T>, T, impl::Improved_LivingImproved_3_<T>>;

template <typename T>
using Improved_Living_4_Improved = std::conditional_t<Livingable<T>, T, impl::Improved_LivingImproved_4_<T>>;

template <typename T>
using Improved = std::conditional_t<Livingable<T>, T, impl::Improved_<T>>;

///////////////////////////////////////////

#include <iostream>
#include "Examples/demangle_type_name.hpp"

using helpers::is_property_improvement;
using helpers::is_same_priority;

struct Empty {};

static_assert(is_same_priority<
                Property<Living>,
                Property<Living_1_Improved>>);
static_assert(is_same_priority<
                Property<Living_1_Improved>,
                Property<Living_2_Improved>>);
static_assert(is_same_priority<
                Property<Living_2_Improved>,
                Property<Improved_Living_3_Improved>>);
static_assert(is_same_priority<
                Property<Improved_Living_3_Improved>,
                Property<Improved_Living_4_Improved>>);

int main() {
    static_assert(Property<Living>::value == Property<Living_impl>::value);
    static_assert(is_same_priority<Property<Living>, Property<Living_impl>>);

    auto print = []<template <typename...> typename property>() {
        std::cout << name<Property<property>>() << " priority = " << Property<property>::value << " | improved = " << is_property_improvement<property> << '\n';
    };

    std::cout << "properties can be improved" << '\n';
    print.operator()<Living>();
    print.operator()<Living_1_Improved>();
    print.operator()<Living_2_Improved>();
    print.operator()<Improved_Living_3_Improved>();
    print.operator()<Improved_Living_4_Improved>();
    print.operator()<Improved>();

    Living<Naming<Empty>> obj1{Name{"test"}, Health{5}};
    Living_1_Improved<Naming<Empty>> obj2{Name{"test"}, Health{15}};
    Living_2_Improved<Naming<Empty>> obj3{Name{"test"}, Health{45}};
    Improved_Living_3_Improved<Naming<Empty>> obj4{Name{"test"}, Health{145}};
    Improved_Living_4_Improved<Naming<Empty>> obj5{Name{"test"}, Health{199}};

    static_assert(Livingable<decltype(obj1)>);
    static_assert(Livingable<decltype(obj2)>);
    static_assert(Livingable<decltype(obj3)>);
    static_assert(Livingable<decltype(obj4)>);
    static_assert(Livingable<decltype(obj5)>);

    std::cout << '\n';
    std::cout << name<decltype(obj1)>() << " = " << traits::accessHealth::get(obj1).value() << '\n';
    std::cout << name<decltype(obj2)>() << " = " << traits::accessHealth::get(obj2).value() << '\n';
    std::cout << name<decltype(obj3)>() << " = " << traits::accessHealth::get(obj3).value() << '\n';
    std::cout << name<decltype(obj4)>() << " = " << traits::accessHealth::get(obj4).value() << '\n';
    std::cout << name<decltype(obj5)>() << " = " << traits::accessHealth::get(obj5).value() << '\n';

    std::cout << '\n';
#ifdef NO_PREMADE_PROPERTIES
    std::cout << obj1.getType<Health>().value() << '\n';
#else
    std::cout << obj1.getHealth().value() << '\n';
#endif
    std::cout << obj2.hp.value() << '\n';
    std::cout << obj3.getHealth().value() << '\n';
    std::cout << obj4.getHealth().value() << '\n';
    std::cout << obj5.getHealth().value() << '\n';
}
