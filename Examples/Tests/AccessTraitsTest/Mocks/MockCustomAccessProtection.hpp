#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/ProtectionTraits.hpp"

struct MockCustomAccessProtection {
    MOCK_METHOD(Protection&, get, (TestType& el));
    MOCK_METHOD(const Protection&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessProtection<T> {
    static MockCustomAccessProtection* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};

template <>
MockCustomAccessProtection* traits::CustomAccessProtection<TestType>::mock = nullptr;
