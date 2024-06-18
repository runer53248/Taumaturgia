#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Traits/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(Protection);
MOCK_METHOD(Protection&, get_, (TestType & el));
MOCK_METHOD(const Protection&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Protection);
#else
template <typename T>
struct traits::CustomAccessProtection {
    inline static traits::CustomAccessProtection<T>* mock = nullptr;

    MOCK_METHOD(Protection&, get_, (TestType & el));
    MOCK_METHOD(const Protection&, get_, (const TestType& el));

    static constexpr decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessProtection!");
    }
};

template <typename T>
using CustomAccessProtectionMock = traits::CustomAccessProtection<T>;
#endif
