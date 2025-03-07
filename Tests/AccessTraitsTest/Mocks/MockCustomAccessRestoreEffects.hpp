#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
StartCustomAccessMock(RestoreEffects);
MOCK_METHOD(EffectTypeContainer&, get_, (TestType & el));
MOCK_METHOD(const EffectTypeContainer&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(RestoreEffects);
#else
template <typename T>
struct traits::CustomAccessType<EffectTypeContainer, T> {
    inline static traits::CustomAccessType<EffectTypeContainer, T>* mock = nullptr;

    MOCK_METHOD(EffectTypeContainer&, get_, (TestType & el));
    MOCK_METHOD(const EffectTypeContainer&, get_, (const TestType& el));

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessRestoreEffects!");
    }
};

template <typename T>
using CustomAccessRestoreEffectsMock = traits::CustomAccessType<EffectTypeContainer, T>;
#endif
