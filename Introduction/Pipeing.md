# Pipeing

Types of pipeing in project:

1. Preparing of creator to make object intantion.

- with global ordering (based on order_list defined in code)

```cpp
using order_list = taged_list<
    Damaging,
    Protecting>;

...
struct Base{};
auto create_type =
    From::base<Base>              //
    | With::user_property<int>    //
    | With::property<Protecting>  //
    | With::Damage                //
    ;
auto type = create_type(
            Damage{5, DamageType::Physical},    // earlier on order_list
            Protection{10, BodyLocation::Legs}, // later on order_list
            15);                                // not on order_list
```

- with custom ordering (ordered as given)

```cpp
struct Base{};
auto create_type =
    From::base<Base>                       //
    | WithUnordered::user_property<int>    // first: int
    | WithUnordered::property<Protecting>  // later: Protecting
    | WithUnordered::Damage                // last: Damage
    ;
auto type = create_type(
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical});
```

2. Create or expand a list of properties.

```cpp
list with_list_Name = With::Name; // implicit conversion from Property<Naming> to list<Naming<tag>>
auto tlist = With::Name | With::Health | With::Protection | With::Damage;
auto nlist = tlist | With::user_property<int>;
```

3. Modify existing object with needed properties.

- with list of properties

```cpp
struct Base{int x{}; int y{};};
Base base_type{default_x, default_y};
auto tlist = With::Name | With::Health | With::Protection | With::Damage; // order as given
auto new_type = base_type | tlist;
auto new_type2 = base_type | (With::Name | With::Health | With::Protection | With::Damage);
auto new_type3 = Base{default_x, default_y} | tlist;
```

- with properties forwarding until Create object is pass (meaning readiness to create resulting type).

```cpp
struct Base{int x{}; int y{};};
Base base_type{default_x, default_y};
auto new_type = 
    base_type           //
    | With::Name        //
    | With::Health      //
    | With::Protection  //
    | Create            //
    ;
```
