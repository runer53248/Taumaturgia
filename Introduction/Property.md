# Property

***`Property`*** is a member of specific type that can be accessed. <br>
Each ***`property`*** has a single type to which it encapsulates access. <br> ***`Concepts`*** determine whether the type meets the requirements imposed on ***`properties`***. <br> Build-in ***`properties`*** constructors allow ignore or create its member in many ways (ie. by variant, from tuple, as unordered) and in conjunction with others ***`properties`***.
<br> User can create build-in like ***`properties`*** using ***`UserProperty`*** class. <br>

To validate property existance use ***`traits feature`***.

```cpp
using PROPERTY_TYPE = float; // type encapsulated by property
template <typename T>
concept PROPERTYable = trait_accessable<T, PROPERTY_TYPE>;

static_assert(PROPERTYable<Type>);
```

### What type is considered as having ***`property`***?

Type need to have way to access it's encapsulates type same as or convertible to ***`property`*** type. <br> As example for concept ***`Namingable`*** this means:

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
#include "Object/Types/Name.hpp"
struct Type {
    Name name{"Valid"};
};
static_assert(Namingable<Type>);
```

2. type that have public ***`getName`*** method returning **std::string** convertible type

```cpp
struct Type {};

template <typename T, typename TYPE>
class WithName : public T {
public:
    WithName() = default;
    explicit WithName(const TYPE& name)
        : name{name} {}

    TYPE& getName() & { return name; }
    const TYPE& getName() const& { return name; }

private:
    TYPE name{"Valid"};
};
using type_1 = WithName<Type, const char*>;
using type_2 = WithName<Type, std::string>;
using type_3 = WithName<Type, Name>;
static_assert(Namingable<type_1>);
static_assert(Namingable<type_2>);
static_assert(Namingable<type_3>);
```

3. type with ***`Naming`*** **property**
```cpp
struct Type {};
using named_Type = Naming<Type>;
static_assert(Namingable<named_Type>);
```

4. type that have ***`CustomAccessName`*** **trait** specialization
```cpp
struct Type {
    auto name() & { return Name{"Valid"}; }
    const auto name() const& { return Name{"const Valid"}; }
};

template <typename T> requires std::is_base_of_v<Type, T>
struct traits::CustomAccessName<T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.name();
    }
};
static_assert(Namingable<Type>);
```
