#pragma once
#include <string>
#include <type_traits>

// struct Name;

template <typename T>
concept NameAccessable = requires(T x) {
    x.name;
    std::is_convertible_v<decltype(T::name), std::string>;
};

template <typename T>
concept GetNameAccessable = requires(T x) {
    x.getName();
    { x.getName() } -> std::convertible_to<std::string>;
};

namespace traits {

template <typename T>
struct CustomAccessName {};

template <typename T>
concept CustomNameAccessable = requires(T x) {
    CustomAccessName<T>::get(x);
    { CustomAccessName<T>::get(x) } -> std::convertible_to<std::string>;
};

struct accessName {
    static auto& get(NameAccessable auto& el) {
        return el.name;
    }

    static auto& get(GetNameAccessable auto& el) {
        return el.getName();
    }

    template <CustomNameAccessable T>
    static auto& get(T& el) {
        return CustomAccessName<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
