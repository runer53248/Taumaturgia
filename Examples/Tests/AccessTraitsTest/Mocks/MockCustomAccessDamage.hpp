#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/DamageTraits.hpp"

struct MockCustomAccessDamage {
    MOCK_METHOD(Damage &, get, (TestType& el));
    MOCK_METHOD(const Damage &, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessDamage <TestType> {
    static MockCustomAccessDamage * mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
        // return el.getDamage();
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
        // return el.getDamage();
    }
};
MockCustomAccessDamage * traits::CustomAccessDamage<TestType>::mock = nullptr;
