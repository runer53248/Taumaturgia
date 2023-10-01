#pragma once
#include <string>
#include <type_traits>
#include <utility>  //for as_const

// struct Name;

template <typename T>
concept NameAccessable = requires(T x) {
    x.name;
    std::is_convertible_v<decltype(T::name), std::string>;
};

template <typename T>
concept GetNameAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getName() } -> std::convertible_to<std::string>;
    { y.getName() } -> std::convertible_to<const std::string>;
};

namespace traits {

template <typename T>
struct CustomAccessName {};

template <typename T>
concept CustomNameAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessName<T>::get(x) } -> std::convertible_to<std::string>;
    { CustomAccessName<T>::get(y) } -> std::convertible_to<const std::string>;
};

struct accessName {
    static auto& get(NameAccessable auto& el) {
        return el.name;
    }

    template <GetNameAccessable T>
        requires(not CustomNameAccessable<T>)  // use custom access if available
    static decltype(auto) get(T& el) {
        return el.getName();
    }

    template <CustomNameAccessable T>
    static decltype(auto) get(T& el) {
        return CustomAccessName<std::remove_cv_t<T>>::get(el);
    }

    template <CustomNameAccessable T>
    static decltype(auto) get(const T& el) {
        return CustomAccessName<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
