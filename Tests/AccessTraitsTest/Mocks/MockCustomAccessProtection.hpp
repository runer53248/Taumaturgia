#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
StartCustomAccessMock(Protection);
MOCK_METHOD(Protection&, get_, (TestType & el));
MOCK_METHOD(const Protection&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Protection);
#else
template <typename T>
struct traits::CustomAccessType<Protection, T> {
    inline static traits::CustomAccessType<Protection, T>* mock = nullptr;

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
using CustomAccessProtectionMock = traits::CustomAccessType<Protection, T> ;
#endif
