#pragma once
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

namespace impl {

template <typename T, typename Base, size_t DIG>
concept parent_digingable = requires(T t) {
    static_cast<const Base&>(t).template getType<DIG - 1>();
};

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename T>
class GetFeatures;

template <typename TYPE, typename T, typename... Tags>
class GetFeatures<UserProperty_<TYPE, T, Tags...>> {
public:
    using improvement_of = UserProperty_<TYPE, T, Tags...>;  // will act like same type if TYPE and Tags are same

    // MARK: getType<TYPE, size_t>

    template <typename RETURN = TYPE, size_t DIG = 0, typename Self>
        requires std::same_as<RETURN, TYPE>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        if constexpr (DIG) {
            if constexpr (getType_template_able<T, RETURN>) {
                return static_cast<type>(self).template getType<RETURN, DIG - 1>();
            }
        } else {
            // return (self.type_);
            return (self.getT());
        }
    }

    template <typename RETURN, size_t DIG = 0, typename Self>
        requires(not std::same_as<RETURN, TYPE> and getType_template_able<T, RETURN>)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        // if constexpr (trait_accessable<T, RETURN>) {
        //     return trait<RETURN>::get(static_cast<type>(self));
        // } else
        if constexpr (getType_template_able<T, RETURN>) {
            return static_cast<type>(self).template getType<RETURN, DIG>();
        } else {
            // static_assert(false, "WARNING: getType method tries to return void type");
        }
    }

    template <typename RETURN, size_t DIG = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    // MARK: getType<size_t>

    template <size_t DIG, typename Self>
        requires(DIG == 0)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        // return (self.type_);
        return (self.getT());
    }

    template <size_t DIG, typename Self>
        requires((DIG > 0) and parent_digingable<Self, T, DIG>)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        return static_cast<type>(self).template getType<DIG - 1>();
    }

    template <size_t DIG, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    // MARK: haveTypeNum

    template <typename RETURN = TYPE, size_t NUM = 0>
        requires have_getType_type_num_method<improvement_of, RETURN, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <typename RETURN = TYPE, size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    template <size_t NUM>
        requires have_getType_num_method<improvement_of, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <size_t NUM>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags, typename Self>
        requires std::same_as<list<RETURN, TTags...>, list<TYPE, Tags...>>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        // return (self.type_);
        return (self.getT());
    }

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        return static_cast<type>(self).template getTypeTaged<RETURN, TTags...>();
    }

    template <typename RETURN, typename... TTags, typename Self>
        requires(not have_getTypeTaged_method<T, RETURN, TTags...>  //
                 and not std::same_as<list<RETURN, TTags...>, list<TYPE, Tags...>>)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;

    // MARK: getTypeOf

    template <typename RETURN, typename... TTags, typename Self>
        requires have_getTypeTaged_method<Self, RETURN, TTags...>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept {
        return self.template getTypeTaged<RETURN, TTags...>();
    }

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept = delete;

    // MARK: getTypeOfSignature

    template <typename Signature, typename Self>
        requires have_getTypeOf_method<Self, Signature>
    constexpr decltype(auto) getTypeOfSignature(this Self& self) noexcept {
        return self.getTypeOf(Signature{});
    }
    template <typename Signature, typename Self>
    constexpr decltype(auto) getTypeOfSignature(this Self& self) noexcept = delete;

    // MARK: getTaged<SKIP, TTags>

    template <size_t SKIP, typename... TTags, typename Self>
        requires std::same_as<list<TTags...>, list<Tags...>>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        if constexpr (SKIP > 0) {
            return static_cast<type>(self).template getTaged<SKIP - 1, TTags...>();  // skip
        } else if constexpr (have_getTypeTaged_method<Self, TYPE, TTags...>) {
            return self.template getTypeTaged<TYPE, TTags...>();  // return by tags and current type
        }
    }
    template <size_t SKIP, typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        return static_cast<type>(self).template getTaged<SKIP, TTags...>();  // skip - diffrent tags
    }

    // MARK: getTaged<TTags...>

    template <typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return self.template getTaged<0, TTags...>();
    }
};
}  // namespace impl
