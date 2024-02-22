#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/NameTraits.hpp"

struct MockCustomAccessName {
    MOCK_METHOD(Name&, get, (TestType& el));
    MOCK_METHOD(const Name&, getConst, (const TestType& el));
};

template <typename T>
    requires std::is_base_of_v<TestType, std::remove_cvref_t<T>>
struct traits::CustomAccessName<T> {
    static MockCustomAccessName* mock;

    static decltype(auto) get(TestType& el) {
        return mock->get(el);
    }

    static decltype(auto) get(const TestType& el) {
        return mock->getConst(el);
    }
};

template <>
MockCustomAccessName* traits::CustomAccessName<TestType>::mock = nullptr;
