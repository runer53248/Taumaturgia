#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
StartCustomAccessMock(CureHealth);
MOCK_METHOD(CureHealth&, get_, (TestType & el));
MOCK_METHOD(const CureHealth&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(CureHealth);
#else
template <typename T>
struct traits::CustomAccessType<CureHealth, T> {
    inline static traits::CustomAccessType<CureHealth, T>* mock = nullptr;

    MOCK_METHOD(CureHealth&, get_, (TestType & el));
    MOCK_METHOD(const CureHealth&, get_, (const TestType& el));

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessCureHealth!");
    }
};

template <typename T>
using CustomAccessCureHealthMock = traits::CustomAccessType<CureHealth, T>;
#endif
