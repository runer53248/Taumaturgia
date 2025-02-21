#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
StartCustomAccessMock(Health);
MOCK_METHOD(Health&, get_, (TestType & el));
MOCK_METHOD(const Health&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Health);
#else
template <typename T>
struct traits::CustomAccessType<Health, T> {
    inline static traits::CustomAccessType<Health, T>* mock = nullptr;

    MOCK_METHOD(Health&, get_, (TestType & el));
    MOCK_METHOD(const Health&, get_, (const TestType& el));

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessHealth!");
    }
};

template <typename T>
using CustomAccessHealthMock = traits::CustomAccessType<Health, T>;
#endif
