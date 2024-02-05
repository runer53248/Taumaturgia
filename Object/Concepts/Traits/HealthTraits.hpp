#pragma once
#include "helper/same_as_ref.hpp"

struct Health;

namespace traits {

template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getHp() } -> same_as_ref<Health>;
    { y.getHp() } -> same_as_ref<const Health>;
};

template <typename T>
struct CustomAccessHealth {};

template <typename T>
concept CustomHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessHealth<T>::get(x) } -> same_as_ref<Health>;
    { CustomAccessHealth<T>::get(y) } -> same_as_ref<const Health>;
};

template <typename T>
concept UserTypeHealthAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<Health>() } -> same_as_ref<Health>;
    { y.template getType<Health>() } -> same_as_ref<const Health>;
};

struct accessHealth {
    static auto& get(HealthAccessable auto& el) {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not CustomHealthAccessable<T> and not UserTypeHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getHp();
    }

    template <CustomHealthAccessable T>
        requires(not UserTypeHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessHealth<std::remove_cv_t<T>>::get(el);
    }

    template <CustomHealthAccessable T>
        requires(not UserTypeHealthAccessable<T>)
    static decltype(auto) get(const T& el) {
        return CustomAccessHealth<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeHealthAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Health>();
    }

    template <UserTypeHealthAccessable T>
    static decltype(auto) get(const T& el) {
        return el.template getType<Health>();
    }
};

}  // namespace traits
