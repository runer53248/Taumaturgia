#pragma once
#include <gmock/gmock.h>
#include "Usage/Traits.hpp"

#ifdef CUSTOM_ACCESS_MOCK_MACRO
#include "MockCustomAccess.hpp"
StartCustomAccessMock(Name);
MOCK_METHOD(Name&, get_, (TestType & el));
MOCK_METHOD(const Name&, get_, (const TestType& el));
EndCustomAccessMock();
CustomMock(Name);
#else
template <typename T>
struct traits::CustomAccessType<Name, T> {
    inline static traits::CustomAccessType<Name, T>* mock = nullptr;

    MOCK_METHOD(Name&, get_, (TestType & el));
    MOCK_METHOD(const Name&, get_, (const TestType& el));

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        if (mock) {
            return mock->get_(el);
        }
        throw std::logic_error("Mock not set for CustomAccessName!");
    }
};

static_assert(traits::helpers::CustomTypeAccessable<TestType, Name>);

template <typename T>
using CustomAccessNameMock = traits::CustomAccessType<Name, T>;
#endif
