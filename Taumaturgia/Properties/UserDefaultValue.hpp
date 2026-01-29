#pragma once
#include "Taumaturgia/Properties/Helpers/Tags.hpp"

template <typename T, isTag TAGS = Tags<>>
struct UserDefaultValue {
    static constexpr auto value = [] { return T{}; };
};

template <typename T>
struct buildin_defaults {
    constexpr buildin_defaults() {
        setAsUserDefault();
    }

    static void set(const T& value) {
        value_ = value;
    }
    static void setAsUserDefault() {
        value_ = UserDefaultValue<T, Tags<>>::value();
    }
    static auto get() {
        return value_;
    }

private:
    static T value_;
};

template <typename... Args>
struct prepare_buildin_defaults {  // instantiate after specializations of UserDefaultValue
    constexpr prepare_buildin_defaults() {
        (buildin_defaults<Args>::setAsUserDefault(), ...);
    }

    static void operator ()() {
        (buildin_defaults<Args>::setAsUserDefault(), ...);
    }
};

template <typename T>
T buildin_defaults<T>::value_{};
