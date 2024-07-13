#include <iostream>
#include "Examples/demangle_type_name.hpp"
#include "Taumaturgia/Properties/Helpers/have_properties.hpp"
#include "Usage/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct Type {
    Name name;
};

template <typename T>
using IntProperty = UserProperty<int, T>;

template <typename T>
using FloatProperty = UserProperty<float, T>;

using living_type = add_properties<Type, Living>;
using int_property_type = add_properties<Type, IntProperty>;
using float_property_type = add_properties<Type, FloatProperty>;
using int_float_property_type = add_properties<Type, IntProperty, FloatProperty>;

static_assert(have_properties<living_type,
                              Living>);
static_assert(have_properties<int_property_type,
                              IntProperty>);
static_assert(have_properties<float_property_type,
                              FloatProperty>);
static_assert(have_properties<int_float_property_type,
                              FloatProperty>);
static_assert(have_properties<int_float_property_type,
                              IntProperty,
                              FloatProperty>);

using living_type = add_properties<Type, Living>;  // duplication of living_type

static_assert(have_properties<living_type,
                              Living_impl>);

using living_healing_type = add_properties<Type, Living, Healing>;

static_assert(have_properties<living_healing_type,
                              Living_impl,
                              Healing_impl>);
static_assert(have_properties<living_healing_type,
                              Healing_impl>);
static_assert(have_properties<living_healing_type,
                              Healing_impl,
                              Living>);
static_assert(have_properties<living_healing_type,
                              Living,
                              Healing_impl>);
static_assert(have_properties<living_healing_type,
                              Living,
                              Healing>);
static_assert(have_properties<living_healing_type,
                              Healing>);
static_assert(have_properties<living_healing_type,
                              Living>);

static_assert(have_properties<
              add_properties<Type, Living, Healing>,
              Living,
              Living,
              Healing,
              Living_impl,
              Healing_impl>);  // TODO: consider removing duplicates and sorting properties before specialize have_properties
static_assert(have_properties<
              add_properties<Type, Living, Healing>,
              Healing_impl>);
static_assert(not have_properties<
              add_properties<Type, Living>,
              Living_impl,
              Healing_impl>);

int main() {
    std::cout << name<add_properties<Type, IntProperty>>() << '\n';
    std::cout << name<Property<IntProperty>>() << '\n';
    std::cout << name<Property<IntProperty>::apply<tag>>() << '\n';
    std::cout << '\n';
    std::cout << name<add_properties<tag, Living>>() << '\n';
    std::cout << name<Property<Living>::apply<tag>>() << '\n';
    std::cout << '\n';

    std::cout << name<add_properties<Type, Living>>() << '\n';
    std::cout << name<Property<Living>>() << '\n';

    return 0;
}
