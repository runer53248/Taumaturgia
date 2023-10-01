#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/ProtectionTraits.hpp"

struct MockCustomAccessProtection {
    MOCK_METHOD(Protection&, get, (TestType& el));
    MOCK_METHOD(const Protection&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessProtection<TestType> {
    static MockCustomAccessProtection* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
        // return el.getProtection();
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
        // return el.getProtection();
    }
};
MockCustomAccessProtection* traits::CustomAccessProtection<TestType>::mock = nullptr;
