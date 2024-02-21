#pragma once
#include <string>
#include <type_traits>
#include <utility>  // for as_const

struct Name;

namespace traits {

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

template <typename T>
struct CustomAccessName {};

template <typename T>
concept CustomNameAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessName<T>::get(x) } -> std::convertible_to<std::string>;
    { CustomAccessName<T>::get(y) } -> std::convertible_to<const std::string>;
};

template <typename T>
concept UserTypeNameAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<Name>() } -> std::convertible_to<std::string>;
    { y.template getType<Name>() } -> std::convertible_to<const std::string>;
};

struct accessName {
    static auto& get(NameAccessable auto& el) {
        return el.name;
    }

    template <GetNameAccessable T>
        requires(not CustomNameAccessable<T> and not UserTypeNameAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getName();
    }

    template <CustomNameAccessable T>
        requires(not UserTypeNameAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessName<std::remove_cv_t<T>>::get(el);
    }

    template <CustomNameAccessable T>
        requires(not UserTypeNameAccessable<T>)
    static decltype(auto) get(const T& el) {
        return CustomAccessName<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeNameAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Name>();
    }
};

}  // namespace traits
