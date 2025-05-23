#pragma once
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"

namespace impl {

// MARK: Features_

template <typename T>
class Features_ : public T {
public:
    using base_type = typename T::property_data::base_type;
    using T::T;
    using typename T::hold_type;

    // MARK: getType

    template <typename RETURN = hold_type, size_t DIG = 0, typename Self>
        requires std::is_same_v<RETURN, hold_type>
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
            if constexpr (getType_template_able<base_type, RETURN>) {
                return static_cast<base>(self).template getType<RETURN, DIG - 1>();
            }
        } else {
            return trait<RETURN>::get(static_cast<type>(self));
        }
    }

    template <typename RETURN = hold_type, size_t DIG = 0, typename Self>
    constexpr decltype(auto) getType(this Self&& self) noexcept {
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;

        // if constexpr (trait_accessable<base_type, RETURN>) {
        //     return trait<RETURN>::get(static_cast<base>(self));
        // } else
        if constexpr (getType_template_able<base_type, RETURN>) {
            return static_cast<base>(self).template getType<RETURN, DIG>();
        } else {
            // static_assert(false, "WARNING: getType method tries to return void type");
        }
    }

    template <size_t DIG, typename Self>
        requires(DIG == 0)
    constexpr decltype(auto) getType(this Self&& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        return trait<hold_type>::get(static_cast<type>(self));
    }
    template <size_t DIG, typename Self>
    constexpr decltype(auto) getType(this Self&& self) noexcept {
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;

        return static_cast<base>(self).template getType<DIG - 1>();
    }
    template <size_t DIG, typename Self>
        requires(DIG > 0 and not requires(base_type t) { t.template getType<DIG - 1>(); })
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    // MARK: haveTypeNum

    template <typename RETURN, size_t NUM = 0>
        requires have_getType_type_num<Features_<T>, RETURN, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <typename RETURN, size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    template <size_t NUM = 0>
        requires have_getType_num<Features_<T>, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags, typename Self>
        requires(std::same_as<list<>, list<TTags...>>  //
                 and std::same_as<RETURN, hold_type>)
    constexpr decltype(auto) getTypeTaged(this Self&& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (getType_able<type, RETURN>) {
            return static_cast<type>(self).getType();
        } else {
            return trait<RETURN>::get(static_cast<type>(self));
        }
    }
    template <typename RETURN, typename... TTags, typename Self>
    // requires(requires(T t) { t.template getTypeTaged<RETURN, TTags...>(); }  //
    //          or requires(base_type b) { b.template getTypeTaged<RETURN, TTags...>(); })
    constexpr decltype(auto) getTypeTaged(this Self&& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const base_type&,
            base_type&>;

        if constexpr (std::same_as<typename T::property_data::tags_list, list<TTags...>> and
                      requires { static_cast<type>(self).template getTypeTaged<RETURN, TTags...>(); }) {
            return static_cast<type>(self).template getTypeTaged<RETURN, TTags...>();
        } else
        // if constexpr (requires { static_cast<base>(self).template getTypeTaged<RETURN, TTags...>(); })
        {
            return static_cast<base>(self).template getTypeTaged<RETURN, TTags...>();
        }
    }

    template <typename RETURN, typename... TTags, typename Self>
        requires(not(get_type_taged_able<T, RETURN, TTags...> or            //
                     get_type_taged_able<base_type, RETURN, TTags...>) and  //
                 not(std::same_as<list<>, list<TTags...>> and               //
                     std::same_as<RETURN, hold_type>))
    constexpr decltype(auto) getTypeTaged(this Self&& self) noexcept = delete;

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

    template <typename RETURN, typename... TTags, typename Self>
        requires(not get_type_taged_able<Self, RETURN, TTags...>)
    constexpr decltype(auto) getTypeOf(this Self&& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept = delete;

    // MARK: getTypeOfSignature

    template <typename Signature, typename Self>
    constexpr decltype(auto) getTypeOfSignature(this Self&& self) noexcept {
        return self.getTypeOf(Signature{});
    }
    template <typename Signature, typename Self>
        requires(not get_type_of_able<Self, Signature>)
    constexpr decltype(auto) getTypeOfSignature(this Self&& self) noexcept = delete;
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
