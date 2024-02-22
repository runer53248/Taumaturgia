#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/UserTypeTraits.hpp"

template <typename TYPE>
struct MockCustomTypeAccess {
    MOCK_METHOD(TYPE&, get, (TestType& el));
    MOCK_METHOD(const TYPE&, getConst, (const TestType& el));
};

template <typename TYPE>
struct traits::CustomTypeAccess<TestType, TYPE> {
    inline static MockCustomTypeAccess<TYPE>* mock = nullptr;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};
