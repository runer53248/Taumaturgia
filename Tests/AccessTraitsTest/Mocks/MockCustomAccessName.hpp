#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Concepts/Traits/NameTraits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(Name);
MOCK_METHOD(Name&, get_, (TestType & el));
MOCK_METHOD(const Name&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Name);
#else
template <typename T>
struct traits::CustomAccessName {
    inline static traits::CustomAccessName<T>* mock = nullptr;

    MOCK_METHOD(Name&, get_, (TestType & el));
    MOCK_METHOD(const Name&, get_, (const TestType& el));

    static decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessName!");
    }
};

static_assert(traits::CustomNameAccessable<TestType>);

template <typename T>
using CustomAccessNameMock = traits::CustomAccessName<T>;
#endif
