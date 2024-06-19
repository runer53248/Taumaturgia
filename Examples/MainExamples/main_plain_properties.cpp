#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"
#include "Usage/Properties.hpp"

struct Empty {};

//  .  outer  .   .   .  inner  .
// ...<  X  <...<...<...<  X  <...<Empty>>>>>>>

int main() {
    auto most_inner_only_test = []<template <typename> typename T> {
        static_assert(std::is_same_v<
                      T<T<T<Empty>>>,
                      T<Empty>>);
        static_assert(std::is_same_v<
                      B<T<T<T<Empty>>>>,
                      B<T<Empty>>>);
        static_assert(std::is_same_v<
                      T<T<T<B<Empty>>>>,
                      T<B<Empty>>>);
        static_assert(std::is_same_v<
                      T<T<B<T<T<Empty>>>>>,
                      B<T<Empty>>>);  // * most inner only
        static_assert(std::is_same_v<
                      Living<T<T<B<T<T<Damaging<Empty>>>>>>>,
                      Living<B<T<Damaging<Empty>>>>>);  // * most inner only
    };

    most_inner_only_test.operator()<A>();        // * A plain property (using derived_from_property) use most inner only
    most_inner_only_test.operator()<Healing>();  // * build-in Healing properties use most inner only

    auto derived_from_property_test = []<template <typename> typename property> {
        using example_none = Empty;                                                          // no property
        using example_other = Living<Empty>;                                                 // other property
        using example_base = property<Empty>;                                                // just property
        using example_outer_base = property<Protecting<Living<Damaging<Empty>>>>;            // property most outer
        using example_inner_base = Damaging<Living<Protecting<property<Empty>>>>;            // property most inner
        using example_middle_base = Healing<Protecting<property<Living<Damaging<Empty>>>>>;  // property in middle

        static_assert(not derived_from_property<
                      example_none,
                      property>);
        static_assert(not derived_from_property<
                      example_other,
                      property>);
        static_assert(derived_from_property<
                      example_base,
                      property>);
        static_assert(derived_from_property<
                      example_outer_base,
                      property>);
        static_assert(derived_from_property<
                      example_inner_base,
                      property>);
        static_assert(derived_from_property<
                      example_middle_base,
                      property>);
    };

    derived_from_property_test.operator()<impl::A_>();      // without duplication removal feature
    derived_from_property_test.operator()<A>();             // with duplication removal feature
    derived_from_property_test.operator()<Wearing_impl>();  // without duplication removal feature

    derived_from_property_test.operator()<Wearing>();  // with duplication removal feature
}
