#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(CureHealth);
MOCK_METHOD(CureHealth&, get_, (TestType & el));
MOCK_METHOD(const CureHealth&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(CureHealth);
#else
template <typename T>
struct traits::CustomAccessCureHealth {
    inline static traits::CustomAccessCureHealth<T>* mock = nullptr;

    MOCK_METHOD(CureHealth&, get_, (TestType & el));
    MOCK_METHOD(const CureHealth&, get_, (const TestType& el));

    static constexpr decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessCureHealth!");
    }
};

template <typename T>
using CustomAccessCureHealthMock = traits::CustomAccessCureHealth<T>;
#endif
