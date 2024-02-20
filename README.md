# Taumaturgia Project

## Project goal is to create a system that allows creating new types (and modify existing ones) based on features called ***`properties`***. Each ***`property`*** has a single type to which it encapsulates access.

## Type with ***`properties`*** is used to create an instantion of the ***`Object`*** class.

## ***`Object`*** instantions will be used to invoke ***`strategies`*** assigned to individual ***`properties`***.

## What is needed for type to have ***`properties`***?

Concepts determine whether the type meets the requirements imposed on ***`Properties`***.\
There are two ways to add ***`properties`*** to a type.

1. By placing the type in successive layers of ***`properties`***. In this case, the type must have a ***`Namingable`*** property or ***`Naming`*** must be the deepest nested ***`property`***.
```cpp
using NewType = Living<Wearing<Damaging<Protecting<Healing<Restoring<Naming<Type>>>>>>>
```

2. By using ***`add_properties`***. This allows you to specify the preferred order of ***`properties`*** and what should be considered an indexed ***`Property`*** and ordered as such.
```cpp
using NewType = add_properties<Type, Naming, Living, Wearing, Damaging, Protecting, Healing, Restoring>;
```

## What is needed for type to be used in ***`Object`*** class?

By default, all types should satisfy the ***`Namingable`*** concept. This will allow the type to be used in the ***`Object`*** class.\
This means:

1. type that have public ***`name`*** member convertible to **std::string** (or **const std::string**)

```cpp
struct Type {
    const char* name{"Valid"};
};
static_assert(Namingable<Type>);
```

```cpp
struct Type {
    std::string name{"Valid"};
};
static_assert(Namingable<Type>);
```

```cpp
#include "Object/Concepts/Types/Name.hpp"
struct Type {
    Name name{"Valid"};
};
static_assert(Namingable<Type>);
```

2. type that have public ***`getName`*** method returning **std::string** convertible type

```cpp
struct Type {};

template <typename T, typename TYPE>
struct WithName : T {
    WithName() = default;
    explicit WithName(const TYPE& name)
        : name{name} {}

    TYPE& getName() & { return name; }
    const TYPE& getName() const& { return name; }

private:
    TYPE name{"Valid"};
};
static_assert(Namingable<WithName<Type, const char*>>);
static_assert(Namingable<WithName<Type, std::string>>);
static_assert(Namingable<WithName<Type, Name>>);
```

3. type resulted after gived ***`Naming`*** properties
```cpp
struct Type {};
using named_Type = Naming<Type>;
static_assert(Namingable<named_Type>);
```

4. type that have ***`CustomAccessName`*** trait specialization
```cpp
struct Type {
    auto any_name() & { return Name{"Valid"}; }
    const auto any_name() const& { return Name{"const Valid"}; }
};

template <typename T> requires std::is_base_of_v<Type, T>
struct traits::CustomAccessName<T> {
    static auto get(auto& el) {
        return el.any_name();
    }
};
static_assert(Namingable<Type>);
```

## Is there universal method to access property data?
Regardless of how you can access the type stored by a ***`property`***, you can also access it using ***`access traits`***.

```cpp
traits::accessArmorWear::get(type);
traits::accessCureHealth::get(type);
traits::accessDamage::get(type);
traits::accessHealth::get(type);
traits::accessName::get(type);
traits::accessProtection::get(type);
traits::accessRestoreEffects::get(type);
```
```cpp
traits::accessType<ENCAPSULATE_TYPE>::get(type);
```
