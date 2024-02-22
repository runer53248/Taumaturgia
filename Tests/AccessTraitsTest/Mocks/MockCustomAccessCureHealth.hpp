#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/HealthTraits.hpp"

struct MockCustomAccessCureHealth {
    MOCK_METHOD(CureHealth&, get, (TestType& el));
    MOCK_METHOD(const CureHealth&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessCureHealth<T> {
    inline static MockCustomAccessCureHealth* mock = nullptr;

    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            return mock->getConst(el);
        } else {
            return mock->get(el);
        }
    }
};
