#pragma once
#include <gmock/gmock.h>
#include "MockCustomAccess.hpp"
#include "Taumaturgia/Traits/Helpers/CustomAccessType.hpp"

template <typename TYPE, typename T>
struct traits::CustomAccessType {
    inline static traits::CustomAccessType<TYPE, T>* mock = nullptr;

    MOCK_METHOD(TYPE&, get_, (T & el));
    MOCK_METHOD(const TYPE&, get_, (const T& el));

    template <typename TT>
        requires std::same_as<TestType, std::remove_cvref_t<TT>>
    static constexpr decltype(auto) get(TT& el) {
        return mock->get_(el);
    }
};
