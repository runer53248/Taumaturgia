#include "Examples/property_A.hpp"
#include "Examples/property_B.hpp"
#include "Examples/property_C.hpp"
#include "Object/Properties/Properties.hpp"

struct Empty {};

// ! A using derived_from_template_base use most inner only
static_assert(std::is_same_v<
              A<A<A<Empty>>>,
              A<Empty>>);
static_assert(std::is_same_v<
              B<A<A<A<Empty>>>>,
              B<A<Empty>>>);
static_assert(std::is_same_v<
              A<A<A<B<Empty>>>>,
              A<B<Empty>>>);
static_assert(std::is_same_v<
              A<A<B<A<A<Empty>>>>>,
              B<A<Empty>>>);  // ! most inner only
static_assert(std::is_same_v<
              Living<A<A<B<A<A<Damaging<Empty>>>>>>>,
              Living<B<A<Damaging<Empty>>>>>);  // ! most inner only

// B dont have this feature at all

// ! C using propertyable use most outer only
static_assert(std::is_same_v<
              C<C<C<Empty>>>,
              C<Empty>>);
static_assert(std::is_same_v<
              B<C<C<C<Empty>>>>,
              B<C<Empty>>>);
static_assert(std::is_same_v<
              C<C<C<B<Empty>>>>,
              C<B<Empty>>>);
static_assert(std::is_same_v<
              C<C<B<C<C<Empty>>>>>,
              C<B<Empty>>>);  // ! most outer only
static_assert(std::is_same_v<
              Living<C<C<B<C<C<Damaging<Empty>>>>>>>,
              Living<C<B<Damaging<Empty>>>>>);  // ! most outer only

// ! build-in properties use most outer only
static_assert(std::is_same_v<
              Healing<Healing<Healing<Empty>>>,
              Healing<Empty>>);
static_assert(std::is_same_v<
              B<Healing<Healing<Healing<Empty>>>>,
              B<Healing<Empty>>>);
static_assert(std::is_same_v<
              Healing<Healing<Healing<B<Empty>>>>,
              Healing<B<Empty>>>);
static_assert(std::is_same_v<
              Healing<Healing<B<Healing<Healing<Empty>>>>>,
              B<Healing<Empty>>>);  // ! most inner only used in build-in properties
static_assert(std::is_same_v<
              Living<Healing<Healing<B<Healing<Healing<Damaging<Empty>>>>>>>,
              Living<B<Healing<Damaging<Empty>>>>>);  // ! most inner only used in build-in properties

// ! switch order to most outer for build-in properties
template <typename T>
using Healing2 = std::conditional_t<
    propertyable<T, impl::Healing_> or Healingable<T>,
    T,
    impl::Healing_<T>>;

static_assert(std::is_same_v<
              Healing2<Healing2<Healing2<Empty>>>,
              Healing2<Empty>>);
static_assert(std::is_same_v<
              B<Healing2<Healing2<Healing2<Empty>>>>,
              B<Healing2<Empty>>>);
static_assert(std::is_same_v<
              Healing2<Healing2<Healing2<B<Empty>>>>,
              Healing2<B<Empty>>>);
static_assert(std::is_same_v<
              Healing2<Healing2<B<Healing2<Healing2<Empty>>>>>,
              Healing2<B<Empty>>>);  // ! most outer only
static_assert(std::is_same_v<
              Living<Healing2<Healing2<B<Healing2<Healing2<Damaging<Empty>>>>>>>,
              Living<Healing2<B<Damaging<Empty>>>>>);  // ! most outer only

using example_none = Empty;  // no property

using example_other = Living<Empty>;  // other property

template <template <typename> typename BASE>
using example_base = BASE<Empty>;  // just base

template <template <typename> typename BASE>
using example_outer_base = BASE<Protecting<Living<Damaging<Empty>>>>;  // base most outer property

template <template <typename> typename BASE>
using example_inner_base = Damaging<Living<Protecting<BASE<Empty>>>>;  // base most inner properrty

template <template <typename> typename BASE>
using example_middle_base = Healing<Protecting<BASE<Living<Damaging<Empty>>>>>;  // base in middle

template <typename T>
using Base = B<T>;  // without duplication removal feature

// ! checking using propertyable is wrong
static_assert(propertyable<
              example_none,
              Base>);  // ! wrong - should be false
static_assert(propertyable<
              example_other,
              Base>);  // ! wrong - should be false
static_assert(propertyable<
              example_base<Base>,
              Base>);
static_assert(propertyable<
              example_outer_base<Base>,
              Base>);
static_assert(propertyable<
              example_inner_base<Base>,
              Base>);
static_assert(propertyable<
              example_middle_base<Base>,
              Base>);

// * checking using derived_from_template_base is right
static_assert(not derived_from_template_base<
              example_none,
              Base>);
static_assert(not derived_from_template_base<
              example_other,
              Base>);
static_assert(derived_from_template_base<
              example_base<Base>,
              Base>);
static_assert(derived_from_template_base<
              example_outer_base<Base>,
              Base>);
static_assert(derived_from_template_base<
              example_inner_base<Base>,
              Base>);
static_assert(derived_from_template_base<
              example_middle_base<Base>,
              Base>);

int main() {}
