#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Traits/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
StartCustomAccessMock(ArmorWear);
MOCK_METHOD(WearContainer&, get_, (TestType & el));
MOCK_METHOD(const WearContainer&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(ArmorWear);
#else
template <typename T>
struct traits::CustomAccessArmorWear {
    inline static traits::CustomAccessArmorWear<T>* mock = nullptr;

    MOCK_METHOD(WearContainer&, get_, (TestType & el));
    MOCK_METHOD(const WearContainer&, get_, (const TestType& el));

    static constexpr decltype(auto) get(auto& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessArmorWear!");
    }
};

template <typename T>
using CustomAccessArmorWearMock = traits::CustomAccessArmorWear<T>;
#endif
