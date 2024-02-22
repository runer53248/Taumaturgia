#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"

struct MockCustomAccessArmorWear {
    MOCK_METHOD(ProtectionContainer&, get, (TestType& el));
    MOCK_METHOD(const ProtectionContainer&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessArmorWear<T> {
    static MockCustomAccessArmorWear* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};

template <>
MockCustomAccessArmorWear* traits::CustomAccessArmorWear<TestType>::mock = nullptr;
