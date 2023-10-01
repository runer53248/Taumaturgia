#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/NameTraits.hpp"

struct MockCustomAccessName {
    MOCK_METHOD(Name&, get, (TestType& el));
    MOCK_METHOD(const Name&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessName<TestType> {
    static MockCustomAccessName* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
        // return el.getName();
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
        // return el.getName();
    }
};
MockCustomAccessName* traits::CustomAccessName<TestType>::mock = nullptr;
