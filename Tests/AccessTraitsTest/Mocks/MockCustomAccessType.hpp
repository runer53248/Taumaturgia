#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Concepts/Traits/UserTypeTraits.hpp"

template <typename TYPE, typename T>
struct traits::CustomAccessType {
    inline static traits::CustomAccessType<TYPE, T>* mock = nullptr;

    MOCK_METHOD(TYPE&, get_, (T & el));
    MOCK_METHOD(const TYPE&, get_, (const T& el));

    static decltype(auto) get(auto& el) {
        return mock->get_(el);
    }
};
