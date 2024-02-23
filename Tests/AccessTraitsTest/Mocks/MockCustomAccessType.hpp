#pragma once
#include <gmock/gmock.h>
#include "Object/Concepts/Traits/UserTypeTraits.hpp"

#include <iostream>

template <typename TYPE, typename T>
struct MockCustomTypeAccess {
    MOCK_METHOD(TYPE&, get, (T& el));
    MOCK_METHOD(const TYPE&, getConst, (const T& el));
};

template <typename TYPE, typename T>
struct traits::CustomTypeAccess {
    inline static MockCustomTypeAccess<TYPE, T>* mock = nullptr;

    static decltype(auto) get(auto& el) {
        if constexpr (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
            std::cout << "const CustomTypeAccess::get(..)\n";
            return mock->getConst(el);
        } else {
            std::cout << "CustomTypeAccess::get(..)\n";
            return mock->get(el);
        }
    }
};
