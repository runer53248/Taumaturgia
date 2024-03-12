#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Object/Concepts/Traits/DamageTraits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(Damage);
MOCK_METHOD(Damage&, get_, (TestType & el));
MOCK_METHOD(const Damage&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Damage);
#else
template <typename T>
struct traits::CustomAccessDamage {
    inline static traits::CustomAccessDamage<T>* mock = nullptr;

    MOCK_METHOD(Damage&, get_, (TestType & el));
    MOCK_METHOD(const Damage&, get_, (const TestType& el));

    static decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessDamage!");
    }
};

template <typename T>
using CustomAccessDamageMock = traits::CustomAccessDamage<T>;
#endif
