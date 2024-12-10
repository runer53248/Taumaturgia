# Traits

### ***`Access traits`*** feature is used to provide universal way for accessing data. 
### They also restricts type to have it's data accessable by single way.

Normaly data can be accesssed:

1. if its public - by it's name

```cpp
struct Type { Name name; };
Type type;

type.name;
```

2. if own getter is provided - by it's getter

```cpp
class Type { 
    Name name_;
public:
    auto getName() {
        return name_;
    } 
};

type.getName();
```

3. if it's derived

- from build-in ***`property`*** - by its getter

```cpp;
struct Base{};
auto type = Base{} | With::Damage;

type.getDamage();
```

- from user ***`property`*** - by getType getter

```cpp
struct Base{};
auto type = Base{} | With::user_property<std::string>;

type.getType<std::string>();
```

### How to access data using ***`access traits`*** feature
Regardless of how you can access the type stored by a ***`property`*** or br part of type, you can also access it using ***`access traits`***.

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
using ENCAPSULATE_TYPE = int;
traits::accessType<ENCAPSULATE_TYPE>::get(type);
```

Accessibility can be checked by:

```cpp
bool is_accessable = traits::accessArmorWear::template accessable<decltype(type)>;
```

```cpp
using ENCAPSULATE_TYPE = int;
bool is_accessable = traits::accessType<ENCAPSULATE_TYPE>::template accessable<decltype(type)>;
```

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
```

```cpp
struct CustomName { // custom getter
    decltype(auto) name(this auto& self) { 
        return (self.name); 
    }
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
```

### For convinient the different **traits** should be aliased like:

```cpp
template <typename T>
struct trait_ {
    using type = traits::accessType<T>;
};

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

Then its usage is simplified:

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
