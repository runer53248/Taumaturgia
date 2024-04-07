#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(Health);
MOCK_METHOD(Health&, get_, (TestType & el));
MOCK_METHOD(const Health&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Health);
#else
template <typename T>
struct traits::CustomAccessHealth {
    inline static traits::CustomAccessHealth<T>* mock = nullptr;

    MOCK_METHOD(Health&, get_, (TestType & el));
    MOCK_METHOD(const Health&, get_, (const TestType& el));

    static decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessHealth!");
    }
};

template <typename T>
using CustomAccessHealthMock = traits::CustomAccessHealth<T>;
#endif
