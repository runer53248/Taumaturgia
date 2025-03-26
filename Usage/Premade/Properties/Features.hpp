#pragma once
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"

namespace impl {

// MARK: Features_

template <typename T>
class Features_ : public T {
public:
    using base_type = typename T::property_data::base_type;
    using typename T::hold_type;

    using T::T;

    // MARK: getType

    template <typename RETURN = hold_type, size_t DIG = 0, typename Self>
    constexpr decltype(auto) getType(this Self&& self) noexcept {
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (std::is_same_v<RETURN, hold_type>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<base_type, RETURN>) {
                    return static_cast<base>(self).template getType<RETURN, DIG - 1>();
                }
            } else {
                return trait<RETURN>::get(static_cast<type>(self));
            }
        } else {
            if constexpr (getType_template_able<base_type, RETURN>) {
                return static_cast<base>(self).template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }

    template <size_t DIG, typename Self>
    constexpr decltype(auto) getType(this Self&& self) noexcept {
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (DIG) {
            return static_cast<base>(self).template getType<DIG - 1>();
        } else {
            return trait<hold_type>::get(static_cast<type>(self));
        }
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self&& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;

        if constexpr (std::same_as<list<>, list<TTags...>> and std::same_as<RETURN, hold_type>) {
            return self.template getType<RETURN>();
        } else if constexpr (std::same_as<typename T::property_data::tags_list, list<TTags...>> and
                             requires { T{}.template getTypeTaged<RETURN, TTags...>(); }) {
            return static_cast<type>(self).template getTypeTaged<RETURN, TTags...>();
        } else if constexpr (requires { base_type{}.template getTypeTaged<RETURN, TTags...>(); }) {
            return static_cast<base>(self).template getTypeTaged<RETURN, TTags...>();
        }
    }

    // MARK: getTaged

    template <size_t SKIP, typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self&& self) noexcept {
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (std::same_as<list<TTags...>, list<>>) {
            if constexpr (SKIP > 0) {
                return static_cast<base>(self).template getTaged<SKIP - 1>();  // skip
            } else {
                return trait<hold_type>::get(static_cast<type>(self));
            }
        } else {
            return static_cast<base>(self).template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        }
    }

    template <typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self&& self) noexcept {
        return self.template getTaged<0, TTags...>();
    }

    // MARK: getTypeOf

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeOf(this Self&& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept {
        return self.template getTypeTaged<RETURN, TTags...>();
    }

    // MARK: getTypeOfSignature

    template <typename Signature, typename Self>
    constexpr decltype(auto) getTypeOfSignature(this Self&& self) noexcept {
        return self.getTypeOf(Signature{});
    }
};

namespace impl::Test {
using type = int;

struct test_base {};

template <template <typename...> typename property, typename T>
struct test_metadata {
    using base_type = T;
};

template <typename T>
struct test_property : public T {
    using property_data = test_metadata<test_property, T>;
    using hold_type = type;
    
    hold_type type;
};

using tested_type = Features_<test_property<test_base>>;

static_assert(have_get_features<tested_type, type>);

}  // namespace impl::Test

}  // namespace impl
