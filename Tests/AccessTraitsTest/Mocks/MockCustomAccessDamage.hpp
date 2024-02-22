#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/DamageTraits.hpp"

struct MockCustomAccessDamage {
    MOCK_METHOD(Damage&, get, (TestType & el));
    MOCK_METHOD(const Damage&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessDamage<T> {
    inline static MockCustomAccessDamage* mock = nullptr;

    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            return mock->getConst(el);
        } else {
            return mock->get(el);
        }
    }
};
