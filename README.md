# Taumaturgia Project

## Project goal is to create a system that allows build and manipulate new types with ease. For this purpose ***`property`*** feature will be used.

## [Property](Introduction/Property.md)

***`Property`*** is a member of specific type that can be accessed by **traits**.

Property can be validated using traits:

```cpp
static_assert(Namingable<Type>);
static_assert(trait_accessable<Type, Name>);
```

Properies can be added and reordered using:

1. [add_properties](Introduction/add_properties.md) features

```cpp
using NewType = add_properties_ordered<Type, Naming, Living, Wearing>
```

2. [pipeing](Introduction/Pipeing.md) features

```cpp
auto create_type =
    From::base<Type>              //
    | With::Name;                 //
auto type = create_type(Name{"Type"});
```

```cpp
auto new_type = type | (With::Name | With::Health | With::Damage);
```

## [Trait](Introduction/Traits.md)

***`Trait`*** feature is used to provide universal way for accessing data.

```cpp
if constexpr (trait_accessable<int, decltype(type)>) {
    auto value = trait<int>::get(type);
}
```

## Object

***`Object`*** class use type-erasure to hide type for other purpose than use its ***`strategies`***.
<br> ***`Object`*** instantion will be used to invoke ***`strategies`*** assigned to individual ***`properties`***.
<br> Only types with ***`properties`*** that also satisfy the ***`Namingable`*** concept may be used to create an instantion of the ***`Object`*** class.

## Strategy
