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
    inline static MockCustomAccessArmorWear* mock = nullptr;
    
    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            return mock->getConst(el);
        } else {
            return mock->get(el);
        }
    }
};
