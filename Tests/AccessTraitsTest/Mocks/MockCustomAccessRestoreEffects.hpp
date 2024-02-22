#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"

struct MockCustomAccessRestoreEffects {
    MOCK_METHOD(EffectTypeContainer&, get, (TestType& el));
    MOCK_METHOD(const EffectTypeContainer&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessRestoreEffects<T> {
    inline static MockCustomAccessRestoreEffects* mock = nullptr;
    
    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};
