#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"
#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(RestoreEffects);
MOCK_METHOD(EffectTypeContainer&, get_, (TestType & el));
MOCK_METHOD(const EffectTypeContainer&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(RestoreEffects);
#else
template <typename T>
struct traits::CustomAccessRestoreEffects {
    inline static traits::CustomAccessRestoreEffects<T>* mock = nullptr;

    MOCK_METHOD(EffectTypeContainer&, get_, (TestType & el));
    MOCK_METHOD(const EffectTypeContainer&, get_, (const TestType& el));

    static decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessRestoreEffects!");
    }
};

template <typename T>
using CustomAccessRestoreEffectsMock = traits::CustomAccessRestoreEffects<T>;
#endif
