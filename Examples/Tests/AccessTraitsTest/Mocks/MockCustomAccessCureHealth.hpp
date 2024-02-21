#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/HealthTraits.hpp"

struct MockCustomAccessCureHealth {
    MOCK_METHOD(CureHealth&, get, (TestType& el));
    MOCK_METHOD(const CureHealth&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessCureHealth<TestType> {
    static MockCustomAccessCureHealth* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};
MockCustomAccessCureHealth* traits::CustomAccessCureHealth<TestType>::mock = nullptr;
