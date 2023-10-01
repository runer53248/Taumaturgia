#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/HealthTraits.hpp"

struct MockCustomAccessHealth {
    MOCK_METHOD(Health&, get, (TestType& el));
    MOCK_METHOD(const Health&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessHealth<TestType> {
    static MockCustomAccessHealth* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
        // return el.getHp();
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
        // return el.getHp();
    }
};
MockCustomAccessHealth* traits::CustomAccessHealth<TestType>::mock = nullptr;
