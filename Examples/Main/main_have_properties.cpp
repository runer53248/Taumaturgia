#include <boost/core/demangle.hpp>
#include <iostream>
#include "Object/Properties/Properties.hpp"
#include "Object/Properties/UserProperty.hpp"

template <class T>
std::string name() {
    return boost::core::demangle(typeid(T).name());
}

struct Type {
    Name name;
};

template <typename T>
using IntProperty = UserProperty<int, T>;

// ? ----------------------------------------

template <typename T, template <typename> typename... properties>
using have_properties1 = mp_and<
    mp_contains<  //
        typename Scheme<T>::list,
        Property<properties>>...>;

// static_assert(have_properties1<
//               add_properties<Type, Living>,
//               Living>::value);  // ! not check eqivalent properties with same priority

// static_assert(have_properties1<
//               add_properties<Type, IntProperty>,
//               IntProperty>::value);  // ! dont work with UserProperty

static_assert(have_properties1<
              add_properties<Type, Living>,
              impl::Living_>::value);
static_assert(have_properties1<
              add_properties<Type, Living, Healing>,
              impl::Living_,
              impl::Healing_>::value);
static_assert(have_properties1<
              add_properties<Type, Living, Healing>,
              impl::Healing_>::value);
static_assert(not have_properties1<
              add_properties<Type, Living>,
              Living,
              Healing>::value);  // ! wrong because dont work with eqivalent properties anyway

// static_assert(have_properties1<
//               add_properties<Type, Living, Healing>,
//               Living,
//               Healing>::value); // ! not check eqivalent properties with same priority
// static_assert(have_properties1<
//               add_properties<Type, Living, Healing>,
//               Healing>::value); // ! not check eqivalent properties with same priority

// ? ----------------------------------------

template <template <typename> typename property>
class equivalent_properties_predicate {
private:
    template <typename lhp, typename rhp>
    struct equivalent_properties_predicate_impl {
        constexpr static bool value =
            // (std::is_same_v<lhp, rhp>) or                                                       // same property
            (std::is_same_v<typename lhp::type<tag>, typename rhp::type<tag>>) or               // same Property or UserProperty (eg. UserProperty_<int, tag>)
            ((lhp::value == rhp::value) and lhp::value != std::numeric_limits<size_t>::max());  // same priority of known property
    };

public:
    template <typename T>
    using type = equivalent_properties_predicate_impl<T, Property<property>>;
};

template <typename T, template <typename> typename... properties>
using have_properties2 =
    mp_and<
        mp_to_bool<
            mp_count_if<
                typename Scheme<T>::list,
                equivalent_properties_predicate<properties>::template type>>...>;

static_assert(have_properties2<
              add_properties<Type, Living>,
              Living>::value);  // ? check eqivalent properties with same priority

static_assert(have_properties2<
              add_properties<Type, IntProperty>,
              IntProperty>::value);  // ? work with UserProperty

static_assert(have_properties2<
              add_properties<Type, Living>,
              impl::Living_>::value);
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              impl::Living_,
              impl::Healing_>::value);
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Living,
              impl::Healing_>::value);
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              impl::Healing_,
              Living>::value);
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Living,
              Healing>::value);
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Living,
              Living,
              Healing,
              impl::Living_,
              impl::Healing_>::value);  // TODO: consider removing duplicates and sorting properties before specialize have_properties2
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              impl::Healing_>::value);
static_assert(not have_properties2<
              add_properties<Type, Living>,
              impl::Living_,
              impl::Healing_>::value);

// ? ----------------------------------------

int main() {
    std::cout << name<add_properties<Type, IntProperty>>() << '\n';
    std::cout << name<Property<IntProperty>>() << '\n';
    std::cout << name<Property<IntProperty>::type<tag>>() << '\n';
    std::cout << '\n';
    std::cout << name<add_properties<tag, Living>>() << '\n';
    std::cout << name<Property<Living>::type<tag>>() << '\n';
    std::cout << '\n';

    std::cout << name<add_properties<Type, Living>>() << '\n';
    std::cout << name<Property<Living>>() << '\n';

    return 0;
}
