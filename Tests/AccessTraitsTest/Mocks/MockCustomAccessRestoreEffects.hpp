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
    
    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            return mock->getConst(el);
        } else {
            return mock->get(el);
        }
    }
};
