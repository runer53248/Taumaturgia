#pragma once
#include "Taumaturgia/Properties/Helpers/taged_list.hpp"

namespace impl {

template <typename T>
class Features_ : public T {
public:
    using base_type = typename T::property_data::base_type;
    using typename T::hold_type;

    using T::T;

    // MARK: getType

    template <typename RETURN = hold_type, size_t DIG = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (std::is_same_v<RETURN, hold_type>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<base_type, RETURN>) {
                    return base_type::template getType<RETURN, DIG - 1>();
                }
            }
            return trait<RETURN>::get(static_cast<T&>(*this));
        } else {
            if constexpr (getType_template_able<base_type, RETURN>) {
                return base_type::template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }
    template <typename RETURN = hold_type, size_t DIG = 0>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (std::is_same_v<RETURN, hold_type>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<base_type, RETURN>) {
                    return base_type::template getType<RETURN, DIG - 1>();
                }
            }
            return trait<RETURN>::get(static_cast<const T&>(*this));
        } else {
            if constexpr (getType_template_able<base_type, RETURN>) {
                return base_type::template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }

    // MARK: getTaged

    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() & noexcept {
        if constexpr (std::same_as<list<TTags...>, list<>>) {
            if constexpr (SKIP > 0) {
                return base_type::template getTaged<SKIP - 1>();  // skip
            } else {
                return trait<hold_type>::get(static_cast<T&>(*this));
            }
        } else {
            return base_type::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        }
    }
    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
        if constexpr (std::same_as<list<TTags...>, list<>>) {
            if constexpr (SKIP > 0) {
                return base_type::template getTaged<SKIP - 1>();  // skip
            } else {
                return trait<hold_type>::get(static_cast<const T&>(*this));
            }
        } else {
            return base_type::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        }
    }

    template <typename... TTags>
    constexpr decltype(auto) getTaged() & noexcept {
        return getTaged<0, TTags...>();
    }
    template <typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
        return getTaged<0, TTags...>();
    }
};

}  // namespace impl
