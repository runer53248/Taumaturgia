#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"

struct MockCustomAccessRestoreEffects {
    MOCK_METHOD(EffectTypeContainer&, get, (TestType& el));
    MOCK_METHOD(const EffectTypeContainer&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessRestoreEffects<TestType> {
    static MockCustomAccessRestoreEffects* mock;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};
MockCustomAccessRestoreEffects* traits::CustomAccessRestoreEffects<TestType>::mock = nullptr;
