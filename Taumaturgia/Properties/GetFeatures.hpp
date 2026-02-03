#pragma once
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

#include "Taumaturgia/Properties/Helpers/Tags.hpp"

namespace impl {

template <typename T, typename Base, size_t DIG>
concept parent_digingable = requires(T t) {
    static_cast<const Base&>(t).template getType<DIG - 1>();
};

template <typename T, typename S>
using const_like_ref = std::conditional_t<
    std::is_const_v<S>,
    const std::remove_reference_t<T>&,
    std::remove_reference_t<T>&>;

template <typename TYPE, typename T, isTag TAGS>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename T>
class GetFeatures;

template <typename TYPE, typename T, isTag TAGS>
class GetFeatures<UserProperty_<TYPE, T, TAGS>> {
public:
    using improvement_of = UserProperty_<TYPE, T, TAGS>;  // will act like same type if TYPE and Tags are same

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
            return (self.type_);
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
        return (self.type_);
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

    template <typename RETURN, isTag TTAGS = no_tag, typename Self>
        requires std::same_as<list<RETURN, TTAGS>, list<TYPE, TAGS>>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        return (self.type_);
    }

    template <typename RETURN, isTag TTAGS = no_tag, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<Self>,
            const T&,
            T&>;

        return static_cast<type>(self).template getTypeTaged<RETURN, TTAGS>();
    }

    template <typename RETURN, isTag TTAGS = no_tag, typename Self>
        requires(not have_getTypeTaged_method<T, RETURN, TTAGS>  //
                 and not std::same_as<list<RETURN, TTAGS>, list<TYPE, TAGS>>)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;

    // MARK: getTypeOf

    template <typename RETURN, isTag TTAGS = no_tag, typename Self>
        requires have_getTypeTaged_method<Self, RETURN, TTAGS>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTAGS> signature) noexcept {
        return self.template getTypeTaged<RETURN, TTAGS>();
    }

    template <typename RETURN, isTag TTAGS = no_tag, typename Self>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTAGS> signature) noexcept = delete;

    template <typename RETURN,  typename Self>
        requires have_getTypeTaged_method<Self, RETURN, Tags<>>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN> signature) noexcept {
        return self.template getTypeTaged<RETURN, Tags<>>();
    }

    template <typename RETURN, typename Self>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN> signature) noexcept = delete;

    // MARK: getTypeOfSignature

    template <typename Signature, typename Self>
        requires have_getTypeOf_method<Self, Signature>
    constexpr decltype(auto) getTypeOfSignature(this Self& self) noexcept {
        return self.getTypeOf(Signature{});
    }
    template <typename Signature, typename Self>
    constexpr decltype(auto) getTypeOfSignature(this Self& self) noexcept = delete;

    // MARK: getTaged<SKIP, TTAGS>

    template <size_t SKIP, isTag TTAGS = no_tag, typename Self>
        requires(std::same_as<list<TTAGS>, list<TAGS>>  //
                 and SKIP > 0                                 //
                 and have_getTaged_method<const_like_ref<T, Self>, SKIP - 1, TTAGS>)
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return static_cast<const_like_ref<T, Self>>(self).template getTaged<SKIP - 1, TTAGS>();  // skip
    }

    template <size_t SKIP, isTag TTAGS = no_tag, typename Self>
        requires(std::same_as<TTAGS, TAGS>  //
                 and SKIP == 0                                //
                 and have_getTypeTaged_method<Self, TYPE, TTAGS>)
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return self.template getTypeTaged<TYPE, TTAGS>();  // return by tags and current type
    }

    template <size_t SKIP, isTag TTAGS = no_tag, typename Self>
        requires(not std::same_as<TTAGS, TAGS>  //
                 and have_getTaged_method<const_like_ref<T, Self>, SKIP, TTAGS>)
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return static_cast<const_like_ref<T, Self>>(self).template getTaged<SKIP, TTAGS>();  // skip - diffrent tags
    }

    template <size_t SKIP, isTag TTAGS = no_tag, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept = delete;

    // MARK: getTaged<TTAGS>

    template <isTag TTAGS = no_tag, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return self.template getTaged<0, TTAGS>();
    }
};
}  // namespace impl
