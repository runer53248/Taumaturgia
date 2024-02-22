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
    static MockCustomAccessDamage* mock;

    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};

template <>
MockCustomAccessDamage* traits::CustomAccessDamage<TestType>::mock = nullptr;
