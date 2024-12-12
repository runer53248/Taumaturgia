# order_list

The **`order_list`** is a list of all properties that needs to be ordered in created type.
All **`properties`** not on the list are added after those on list with order depending when they are added between themselves.

### How to replace default order_list
The easiest way to use your own **`order_list`** is to:
1. create file and add properties into **`order_list`**:

```cpp
using order_list = taged_list<
    Property1,
    Property2,
    ...
    PropertyN
>;
```

2. in main file add preprocesor definitions

```cpp
#define CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "PATH_TO_ORDER_LIST_FILE"
```

# UserPropertyAdapter and AdvanceUserProperty

```cpp
using simple = UserPropertyAdapter<float>;
using advanced = AdvanceUserProperty<int, struct first_int>;

// examples of user properties
template <typename T>
using simple_property = simple::template type<T>;
template <typename T>
using advanced_property = advanced::template type<T>;

using order_list = taged_list<
    simple_property,
    advanced::order,
    ...
>;
```