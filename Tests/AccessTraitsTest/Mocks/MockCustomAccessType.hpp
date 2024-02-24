#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Object/Concepts/Traits/UserTypeTraits.hpp"

template <typename TYPE, typename T>
struct traits::CustomTypeAccess {
    inline static traits::CustomTypeAccess<TYPE, T>* mock = nullptr;

    MOCK_METHOD(TYPE&, get_, (T & el));
    MOCK_METHOD(const TYPE&, get_, (const T& el));

    static decltype(auto) get(auto& el) {
        return mock->get_(el);
    }
};
