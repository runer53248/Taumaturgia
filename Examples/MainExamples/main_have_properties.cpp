#include <iostream>
#include "../demangle_type_name.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/Properties/UserProperty.hpp"

struct Type {
    Name name;
};

template <typename T>
using IntProperty = UserProperty<int, T>;

template <typename T>
using FloatProperty = UserProperty<float, T>;

// ? ----------------------------------------

using helpers::Scheme;

template <typename T, template <typename...> typename... properties>
concept have_properties1 =
    mp_and<
        mp_contains<
            typename Scheme<T>::list,
            Property<properties>>...>::value;

// ? ----------------------------------------

template <template <typename...> typename property>
class equivalent_properties_predicate {
private:
    template <typename lhp, typename rhp>
    struct equivalent_properties_predicate_impl {
        constexpr static bool value =
            // (std::is_same_v<lhp, rhp>) or                                                       // same property
            (std::is_same_v<typename lhp::template type<tag>, typename rhp::template type<tag>>) or  // same Property or UserProperty (eg. UserProperty_<int, tag>)
            ((lhp::value == rhp::value) and lhp::value != std::numeric_limits<size_t>::max());       // same priority of known property
    };

public:
    template <typename T>
    using type = equivalent_properties_predicate_impl<T, Property<property>>;
};

template <typename T, template <typename...> typename... properties>
concept have_properties2 =
    mp_and<
        mp_to_bool<
            mp_count_if<
                typename Scheme<T>::list,
                equivalent_properties_predicate<properties>::template type>>...>::value;

// ? ----------------------------------------

using living_type = add_properties<Type, Living>;
// static_assert(have_properties1<living_type,
//                                Living>);  // ! not check eqivalent properties with same priority
static_assert(have_properties2<living_type,
                               Living>);  // ? check eqivalent properties with same priority

using int_property_type = add_properties<Type, IntProperty>;
// static_assert(have_properties1<int_property_type,
//                                IntProperty>);  // ! dont work with UserProperty
static_assert(have_properties2<int_property_type,
                               IntProperty>);  // ? work with UserProperty

using float_property_type = add_properties<Type, FloatProperty>;
// static_assert(have_properties1<float_property_type,
//                                FloatProperty>);  // ! dont work with UserProperty
static_assert(have_properties2<float_property_type,
                               FloatProperty>);  // ? work with UserProperty

using int_float_property_type = add_properties<Type, IntProperty, FloatProperty>;
// static_assert(have_properties1<int_float_property_type,
//                                FloatProperty>);  // ! dont work with UserProperty
static_assert(have_properties2<int_float_property_type,
                               FloatProperty>);  // ? work with UserProperty

// static_assert(have_properties1<int_float_property_type,
//                                IntProperty>,     // ! dont work with UserProperty
//                                FloatProperty>);  // ! dont work with UserProperty
static_assert(have_properties2<int_float_property_type,
                               IntProperty,
                               FloatProperty>);  // ? work with UserProperty

static_assert(have_properties1<living_type,
                               impl::Living_>);
static_assert(have_properties2<living_type,
                               impl::Living_>);

using living_healing_type = add_properties<Type, Living, Healing>;

static_assert(have_properties1<living_healing_type,
                               impl::Living_,
                               impl::Healing_>);
static_assert(have_properties2<living_healing_type,
                               impl::Living_,
                               impl::Healing_>);

static_assert(have_properties1<living_healing_type,
                               impl::Healing_>);
static_assert(have_properties2<living_healing_type,
                               impl::Healing_>);

// static_assert(have_properties1<living_healing_type,
//                                impl::Healing_,
//                                Living>);   // ! not check eqivalent properties with same priority
static_assert(have_properties2<living_healing_type,
                               impl::Healing_,
                               Living>);

// static_assert(have_properties1<living_healing_type,
//                                Living,     // ! not check eqivalent properties with same priority
//                                impl::Healing_>);
static_assert(have_properties2<living_healing_type,
                               Living,
                               impl::Healing_>);

// static_assert(have_properties1<living_healing_type,
//                                Living,     // ! not check eqivalent properties with same priority
//                                Healing>);  // ! not check eqivalent properties with same priority
static_assert(have_properties2<living_healing_type,
                               Living,
                               Healing>);

// static_assert(have_properties1<living_healing_type,
//                                Healing>);  // ! not check eqivalent properties with same priority
static_assert(have_properties2<living_healing_type,
                               Healing>);

// static_assert(have_properties1<living_healing_type,
//                                Living>);  // ! not check eqivalent properties with same priority
static_assert(have_properties2<living_healing_type,
                               Living>);

// ? ----------------------------------------

static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Living,
              Living,
              Healing,
              impl::Living_,
              impl::Healing_>);  // TODO: consider removing duplicates and sorting properties before specialize have_properties2
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              impl::Healing_>);
static_assert(not have_properties2<
              add_properties<Type, Living>,
              impl::Living_,
              impl::Healing_>);

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
