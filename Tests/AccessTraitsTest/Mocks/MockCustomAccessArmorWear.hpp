#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"

StartCustomAccessMock(ArmorWear, WearContainer);
MOCK_METHOD(WearContainer&, get_, (TestType & el));
MOCK_METHOD(const WearContainer&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(ArmorWear, WearContainer);
#else

template <typename T>
struct traits::CustomAccessType<WearContainer, T> {
    inline static traits::CustomAccessType<WearContainer, T>* mock = nullptr;

    MOCK_METHOD(WearContainer&, get_, (TestType & el));
    MOCK_METHOD(const WearContainer&, get_, (const TestType& el));

    static constexpr decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessType<WearContainer, T>!");
    }
};

template <typename T>
using CustomAccessArmorWearMock = traits::CustomAccessType<WearContainer, T>;
#endif
