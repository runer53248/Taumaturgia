# add_property aliases

***`add_property`*** aliases can be used to modify type by adding new properties or changing its order.

### How to add build-in ***`properties`*** to type?

There are two ways to add ***`properties`*** to a type.

1. By placing the type in successive layers of ***`properties`***. This method don't reorder properties but removes redundant and unneeded properties.

```cpp
// deprecated way
using NewType = Living<Wearing<Damaging<Protecting<Healing<Restoring<Naming<Type>>>>>>>
```

2. By using one of fallowed: ***`add_properties_ordered`***, ***`add_properties_unordered`***,***`add_properties`***. This allows you to specify the preferred order of ***`properties`*** and what should be considered an indexed ***`Property`*** and ordered as such.

```cpp
// ordered
using NewType_1 = add_properties_ordered<Type, Naming, Living, Wearing>;
using NewType_2 = add_properties<Type, Property<Naming>, Property<Living>, Property<Wearing>>;
```

```cpp
// unordered
using NewType_1 = add_properties_unordered<Type, Naming, Living, Wearing>;
using NewType_2 = add_properties<Type, Property_unordered<Naming>, Property_unordered<Living>, Property_unordered<Wearing>>;
```

We can also add properties to existing object or build creator of it by use of **pipe operator**.

```cpp
auto create_type =
    From::base<Type>              //
    | With::Name                  //
    | With::Health                //
    | With::Damage                //
auto type = create_type(
            Name{"Type"},
            Health{10},
            Damage{5});                                
```

```cpp
Type type{};
auto new_type = 
    type                //
    | With::Name        //
    | With::Health      //
    | With::Damage      //
    | Create            //
    ;
```

```cpp
Type type{};
auto new_type = type | (With::Name | With::Health | With::Damage);
```
