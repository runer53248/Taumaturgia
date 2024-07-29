#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(Damage);
MOCK_METHOD(Damage&, get_, (TestType & el));
MOCK_METHOD(const Damage&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Damage);
#else
template <typename T>
struct traits::CustomAccessType<Damage, T> {
    inline static traits::CustomAccessType<Damage, T>* mock = nullptr;

    MOCK_METHOD(Damage&, get_, (TestType & el));
    MOCK_METHOD(const Damage&, get_, (const TestType& el));

    static constexpr decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessDamage!");
    }
};

template <typename T>
using CustomAccessDamageMock = traits::CustomAccessType<Damage, T>;
#endif
