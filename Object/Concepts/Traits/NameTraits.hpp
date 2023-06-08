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
struct customAccessName {};

template <typename T>
concept CustomNameAccessable = requires(T x) {
    customAccessName<T>::get(x);
    { customAccessName<T>::get(x) } -> std::convertible_to<std::string>;
};

struct accessName {
    template <NameAccessable T>
    static auto& get(T& el) {
        return el.name;
    }

    template <GetNameAccessable T>
    static auto& get(T& el) {
        return el.getName();
    }

    template <CustomNameAccessable T>
    static auto& get(T& el) {
        return customAccessName<T>::get(el);
    }

    template <CustomNameAccessable T>
    static auto& get(const T& el) {
        return customAccessName<T>::get(el);
    }
};

}  // namespace traits
