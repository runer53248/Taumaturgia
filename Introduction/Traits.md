# Traits

### **`Access traits`** feature is used to provide universal way for accessing data and it restrict single way of access. 

The ***trait_accessable*** concept confirm that getters return reference as it's also needed as setter.

## Ways of accessing data checked by **`Access traits`** feature:

<details>
<summary>
1. it's name 
(if it's same to build-in <strong><code>access trait</code></strong> or named <em><strong>type</strong></em>)
</summary>

```cpp
struct Type { Name name; };
Type type;

type.name;
```
</details>
<details>
<summary>
2. it's getter 
(if it's name like build-in <strong><code>access trait</code></strong> for given type or like <em><strong>getType</strong></em>)
</summary>

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
</details>
<details>
<summary>
3. build-in getter
(if it's derived from build-in <strong><code>property</code></strong>)
</summary>

```cpp
struct Base{};
auto type = Base{}  //
    | With::Damage  //
    | Create;       //

#ifndef NO_PREMADE_PROPERTIES
type.getDamage(); // when With::Damage is build-in property
#else
type.getType();   // when With::Damage is based on UserProperty
#endif
```
</details>
<details>
<summary>
4. build-in 
<em><strong>getType<></strong></em>, 
<em><strong>getTypeTaged<></strong></em>, 
<em><strong>getTypeLike<></strong></em>, 
<em><strong>getTaged<></strong></em> getters 
(if it's derived from user <strong><code>property</code></strong>)
</summary>

```cpp
struct Base{};
auto type = Base{}                             //
    | With::user_property<int>                 //
    | With::user_property<std::string>         //
    | With::user_property<std::string, Base>   //
    | Create;                                  //

type.getType<>();            // results int - closest getType
type.getType<std::string>(); // results first std::string

// results second std::string
type.getType<std::string, 1>();
type.getTypeTaged<std::string, Base>();
using build_list = list<std::string, Base>;
type.getTypeLike<build_list>();
type.getTaged<Base>();
```
</details>
<details>
<summary>
5. <strong>traits::CustomAccessType</strong> specialization
(for custom getters or public members)
</summary>

```cpp
struct Base {
    Name very_specific_name;
};

template <typename T>
    requires std::is_base_of_v<Base, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.very_specific_name);
    }
};

Base type;
traits::CustomAccessType<Name, std::remove_cvref_t<decltype(type)>>::get(type);
```
</details>

## How to access data from custom name, getter or other ways

For data that can be accessed in other ways (or not at all) **`access traits`** feature provide struct **traits::CustomAccessType** to implement it's specialization.

<details>
<summary>example 1</summary>

```cpp
struct CustomName { // aggregate with custom Name member
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

</details>
<details>
<summary>example 2</summary>

```cpp
struct CustomName { // struct with custom Name getter
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
```

</details>

<details>
<summary>example 3</summary>

```cpp
struct CustomName { // struct without Name member
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

</summary>
</details>

```cpp
// usage
CustomName type{};
auto value = trait<Name>::get(type);
// auto value_2 = type.other; // for example 1
// auto value_2 = type.name(); // for examples 2-3
```

## Access data using **`access traits`** feature
Regardless of how you normaly access the data, you can also access it using **`access traits`**.

```cpp
// direct version
traits::accessArmorWear::get(type);
traits::accessCureHealth::get(type);
traits::accessDamage::get(type);
```
```cpp
// user type version 
traits::accessType<int>::get(type);
traits::accessType<float>::get(type);
traits::accessType<std::string>::get(type);
```
```cpp
// universal version
trait<WearContainer>::get(type);
trait<CureHealth>::get(type);
trait<Damage>::get(type);

trait<int>::get(type);
trait<float>::get(type);
trait<std::string>::get(type);
```

## Universal getter - ***trait<>***

### The ***trait<>*** is the alias for **`trait access`** struct. 

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
```
### Basic usage of ***trait<>*** getter:
```cpp
auto type =                    //
    Base{}                     //
    | With::Damage             //
    | With::user_property<int> //
    | Create;                  //
auto dmg = trait<Damage>::get(type);
auto value = trait<int>::get(type);
```

## Check accessability - ***trait_accessable<>***

### Accessibility can be checked using ***trait_accessable*** concept. 
The ***trait_accessable<>*** is a concept base on **`trait access`** ***accessable*** member. 

Every **`trait access`** struct should implement ***accessable*** member for ***trait_accessable***.

```cpp
template <typename T, typename TYPE>
concept trait_accessable = trait<TYPE>::template accessable<T>;
```
### Basic usage of ***trait_accessable<>*** for accessibility check:
```cpp
using Type = decltype(type);
bool is_damage_accessable = trait_accessable<Type, Damage>;
bool is_int_accessable = trait_accessable<Type, int>;
```