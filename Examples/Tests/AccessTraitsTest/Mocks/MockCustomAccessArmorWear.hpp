#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"

struct MockCustomAccessArmorWear {
    MOCK_METHOD(ProtectionContainer&, get, (TestType& el));
    MOCK_METHOD(const ProtectionContainer&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessArmorWear<TestType> {
    static MockCustomAccessArmorWear* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};
MockCustomAccessArmorWear* traits::CustomAccessArmorWear<TestType>::mock = nullptr;
