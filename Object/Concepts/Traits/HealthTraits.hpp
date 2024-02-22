#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

struct Health;

namespace traits {

CreateAccessableConcept(Health, hp, Health);
// CreateGetAccessableConcept(Health, Health);
CreateCustomAccessableConcept(Health, Health);
CreateUserTypeAccessableConcept(Health, Health);

template <typename T>
concept GetHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getHp() } -> same_as_ref<Health>;
    { std::as_const(x).getHp() } -> same_as_ref<const Health>;
};

struct accessHealth {
    static auto& get(HealthAccessable auto& el) {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not(CustomHealthAccessable<T> or UserTypeHealthAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getHp();
    }

    template <CustomHealthAccessable T>
        requires(not UserTypeHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeHealthAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Health>();
    }
};

}  // namespace traits
