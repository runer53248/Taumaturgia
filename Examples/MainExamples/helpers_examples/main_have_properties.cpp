#include <iostream>
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct Type {
    Name name;
};

template <typename T>
using IntProperty = UserProperty<int, T>;

template <typename T>
using FloatProperty = UserProperty<float, T>;

template <template <typename...> typename property>
    requires is_property<property>
class equivalent_properties_predicate {
private:
    template <typename lhp, typename rhp>
    struct equivalent_properties_predicate_impl {
        static constexpr bool value =
            // (std::is_same_v<lhp, rhp>) or                                                       // same property
            (std::is_same_v<typename lhp::template type<tag>, typename rhp::template type<tag>>) or  // same Property or UserProperty (eg. UserProperty_<int, tag>)
            ((lhp::value == rhp::value) and lhp::value != std::numeric_limits<size_t>::max());       // same priority of known property
    };

public:
    template <typename T>
    using type = equivalent_properties_predicate_impl<T, Property<property>>;
};

using helpers::Scheme;

//TODO: add have_properties feature
template <typename T, template <typename...> typename... properties>
concept have_properties2 =
    (is_property<properties> and ...) and
    mp_and<
        mp_to_bool<
            mp_count_if<
                typename Scheme<T>::list_t,
                equivalent_properties_predicate<properties>::template type>>...>::value;

using living_type = add_properties<Type, Living>;
using int_property_type = add_properties<Type, IntProperty>;
using float_property_type = add_properties<Type, FloatProperty>;
using int_float_property_type = add_properties<Type, IntProperty, FloatProperty>;

static_assert(have_properties2<living_type,
                               Living>);
static_assert(have_properties2<int_property_type,
                               IntProperty>);
static_assert(have_properties2<float_property_type,
                               FloatProperty>);
static_assert(have_properties2<int_float_property_type,
                               FloatProperty>);
static_assert(have_properties2<int_float_property_type,
                               IntProperty,
                               FloatProperty>);

using living_type = add_properties<Type, Living>;  // duplication of living_type

static_assert(have_properties2<living_type,
                               Living_impl>);

using living_healing_type = add_properties<Type, Living, Healing>;

static_assert(have_properties2<living_healing_type,
                               Living_impl,
                               Healing_impl>);
static_assert(have_properties2<living_healing_type,
                               Healing_impl>);
static_assert(have_properties2<living_healing_type,
                               Healing_impl,
                               Living>);
static_assert(have_properties2<living_healing_type,
                               Living,
                               Healing_impl>);
static_assert(have_properties2<living_healing_type,
                               Living,
                               Healing>);
static_assert(have_properties2<living_healing_type,
                               Healing>);
static_assert(have_properties2<living_healing_type,
                               Living>);

static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Living,
              Living,
              Healing,
              Living_impl,
              Healing_impl>);  // TODO: consider removing duplicates and sorting properties before specialize have_properties2
static_assert(have_properties2<
              add_properties<Type, Living, Healing>,
              Healing_impl>);
static_assert(not have_properties2<
              add_properties<Type, Living>,
              Living_impl,
              Healing_impl>);

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
