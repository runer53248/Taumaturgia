#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(ArmorWear);
MOCK_METHOD(ProtectionContainer&, get_, (TestType & el));
MOCK_METHOD(const ProtectionContainer&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(ArmorWear);
#else
template <typename T>
struct traits::CustomAccessArmorWear {
    inline static traits::CustomAccessArmorWear<T>* mock = nullptr;

    MOCK_METHOD(ProtectionContainer&, get_, (TestType & el));
    MOCK_METHOD(const ProtectionContainer&, get_, (const TestType& el));

    static decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessArmorWear!");
    }
};

template <typename T>
using CustomMock = traits::CustomAccessArmorWear<T>;
#endif
