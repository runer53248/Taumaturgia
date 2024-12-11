# Traits

### ***`Access traits`*** feature is used to provide universal way for accessing data and restricts single way of access. The ***trait_accessable*** concept confirm that getters return reference as it's also needed as setter.

Feature check data accessibility by:

1. it's name (if it's same to build-in ***`access trait`*** or named ***type***)

```cpp
struct Type { Name name; };
Type type;

type.name;
```

2. it's getter (if it's name like build-in ***`access trait`*** for given type or like ***getType***)

```cpp
class Type { 
    Name name_;
public:
    decltype(auto) getName(this auto& self) { return (self.name_); }

    // auto& getName() { return name_; }
    // auto& getName() const { return name_; }
};

type.getName();
```

3. build-in getter - if it's derived from build-in ***`property`***.

```cpp;
struct Base{};
auto type = Base{}  //
    | With::Damage  //
    | Create;       //

type.getDamage();
// type.getType(); // if With::Damage is build-in based on UserProperty 
```

4. ***getType*** getter - if it's derived from user ***`property`***.

```cpp
struct Base{};
auto type = Base{}                      //
    | With::user_property<std::string>  //
    | Create;                           //

type.getType<std::string>();
```

5. **traits::CustomAccessType** specialization - for custom getters or public members.


### How to access data from custom name, getter or other ways

For data that can be accessed in other ways (or not at all) ***`access traits`*** feature provide struct **traits::CustomAccessType** to implement it's specialization.

```cpp
struct CustomName { // aggregate with custom type name
    Name other;
};

template <typename T>
    requires std::is_base_of_v<CustomName, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.other);
    }
};

CustomName type{};
auto value = trait<Name>::get(type);
auto value_2 = type.other;
```

```cpp
struct CustomName { // custom getter
    decltype(auto) name(this auto& self) { return (self.name); }
private:
    Name name_;
};

template <typename T>
    requires std::is_base_of_v<CustomName, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};

CustomName type{};
auto value = trait<Name>::get(type);
auto value_2 = type.name();
```

```cpp
struct CustomName { // no data stored in type
    auto name() & { return Name{"t_custom_name"}; }
    auto name() const& { return Name{"const t_custom_name"}; }
};

template <typename T>
    requires std::is_base_of_v<CustomName, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};

CustomName type{};
auto value = trait<Name>::get(type);
auto value_2 = type.name();
```

### Access data using ***`access traits`*** feature
Regardless of how you normaly access the data, you can also access it using ***`access traits`***.

```cpp
// direct version 
traits::accessArmorWear::get(type);
traits::accessCureHealth::get(type);
traits::accessDamage::get(type);

// general version
trait<WearContainer>::get(type);
trait<CureHealth>::get(type);
trait<Damage>::get(type);
```

### Check accessability
Accessibility can be checked using ***trait_accessable*** alias:

```cpp
using ENCAPSULATE_TYPE = int;
// direct version 
static_assert(traits::accessType<ENCAPSULATE_TYPE>::get(type));
// generall version
static_assert(trait<ENCAPSULATE_TYPE>::get(type));
```

```cpp
using ENCAPSULATE_TYPE = int;
bool is_accessable = trait_accessable<decltype(type), WearContainer>;
bool is_accessable = trait_accessable<decltype(type), ENCAPSULATE_TYPE>;
```

Basic usage of trait:

- for getter

```cpp
auto type =                    //
    Base{}                     //
    | With::Damage             //
    | With::user_property<int> //
    | Create;                  //
auto dmg = trait<Damage>::get(type);
auto value = trait<int>::get(type);
```

- for accessibility check

```cpp
using Type = decltype(type);
bool is_damage_accessable = trait_accessable<Type, Damage>;
bool is_int_accessable = trait_accessable<Type, int>;
```

### The ***`trait`*** is the alias for ***`trait access`*** struct. Every ***`trait access`*** struct should also implement ***accessable*** member for ***trait_accessable*** alias.

```cpp
// general case
template <typename T>
struct trait_ {
    using type = traits::accessType<T>;
};

...

// specialization for Damage
template <>
struct trait_<Damage> {
    using type = traits::accessDamage;
};

... // other trait_ specializations for build-in traits

template <typename T>
using trait = trait_<T>::type;

template <typename T, typename TYPE>
concept trait_accessable = trait<TYPE>::template accessable<T>;
```
