#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
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

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessDamage!");
    }
};

template <typename T>
using CustomAccessDamageMock = traits::CustomAccessType<Damage, T>;
#endif
