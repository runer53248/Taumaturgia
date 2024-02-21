#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/NameTraits.hpp"

struct MockCustomAccessName {
    MOCK_METHOD(Name&, get, (TestType& el));
    MOCK_METHOD(const Name&, getConst, (const TestType& el));
};

template <>
struct traits::CustomAccessName<TestType> {
    static MockCustomAccessName* mock;

    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            return mock->getConst(el);
        } else {
            return mock->get(el);
        }
    }
};
MockCustomAccessName* traits::CustomAccessName<TestType>::mock = nullptr;
