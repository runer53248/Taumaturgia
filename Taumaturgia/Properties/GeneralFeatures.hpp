#pragma once
#include <stdexcept>
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

namespace impl {
inline constinit const char general_features_name[] = "GeneralFeatures";

using types_ptr = std::variant<
    std::nullptr_t,
    Name*,
    EffectTypeContainer*,
    CureHealth*,
    Protection*,
    Damage*,
    WearContainer*,
    Health*>;

// MARK: GeneralFeatures_

template <typename T>
// requires(not std::is_reference_v<T>)
class GeneralFeatures_ : public T {
private:
    template <class TT>
    using trait_accessable_fn = boost::mp11::mp_bool<trait_accessable<T, TT>>;
    using L = boost::mp11::mp_filter<
        trait_accessable_fn,
        // list_of_types, //TODO: order_list -> extract property::hold_type
        list<Name,
             EffectTypeContainer,
             CureHealth,
             Protection,
             Damage,
             WearContainer,
             Health,
             int,
             float>>;

public:
    using base_type = T;

    // MARK: default and Args C-tors

    constexpr GeneralFeatures_() = default;

    template <typename... Args>
    constexpr GeneralFeatures_(Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    constexpr explicit GeneralFeatures_(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: Unordered C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    constexpr GeneralFeatures_(const Unordered&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: Namingable variant C-tors

    template <typename... V, typename... Args>
    constexpr GeneralFeatures_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: variant C-tors

    template <typename... V, typename... Args>
    constexpr GeneralFeatures_([[maybe_unused]] const std::variant<V...>& type, Args&&... args)  // ! not use type
        : T{std::forward<Args>(args)...} {}

    template <typename... V>
    constexpr GeneralFeatures_(const std::variant<V...>& type)
        : T{} {
        ((std::get_if<V>(&type)
              ? (true, trait<std::remove_cvref_t<V>>::get(*this) = std::get<V>(type))
              : true),
         ...);
    }

    // MARK: getType

    template <typename RETURN, size_t DIG = 0, typename Self>
        requires(trait_accessable<T, RETURN>)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using TT = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&, T&>;
        if constexpr (DIG == 0) {
            return trait<RETURN>::get(static_cast<TT>(self));
        }
    }

    template <size_t DIG = 0, typename Self>
        requires(DIG < boost::mp11::mp_size<L>::value)
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using boost::mp11::mp_at_c;
        using base = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&, T&>;

        return trait<mp_at_c<L, DIG>>::get(static_cast<base>(self));
    }

    template <size_t DIG = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    // MARK: haveTypeNum

    template <typename RETURN, size_t NUM = 0>
        requires have_getType_type_num_method<GeneralFeatures_<T>, RETURN, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <typename RETURN, size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    template <size_t NUM = 0>
        requires have_getType_num_method<GeneralFeatures_<T>, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags, typename Self>
        requires(std::same_as<list<>, list<TTags...>> and
                 have_getType_type_method<Self, RETURN>)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        return self.template getType<RETURN>();
    }

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        return static_cast<type>(self).template getTypeTaged<RETURN, TTags...>();
    }
    template <typename RETURN, typename... TTags, typename Self>
        requires(not have_getTypeTaged_method<T, RETURN, TTags...>  //
                 and not(std::same_as<list<>, list<TTags...>> and   //
                         have_getType_type_method<Self, RETURN>))
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;

    // MARK: getTypeOf

    template <typename RETURN, typename... TTags, typename Self>
        requires(have_getTypeTaged_method<Self, RETURN, TTags...>)
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

    // MARK: getTaged

    template <size_t SKIP, typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (have_getTaged_method<T, SKIP, TTags...>) {
            return static_cast<type>(self).template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        } else if constexpr (std::same_as<list<>, list<TTags...>>) {
            return self.template getBuildinTypes<SKIP>(types_ptr{});
        }
    }

    template <typename... TTags, typename Self>
    constexpr decltype(auto) getTaged(this Self& self) noexcept {
        return self.template getTaged<0, TTags...>();
    }

private:
    template <size_t SKIP, typename TYPE_P, typename... REST_P, typename Self>
    constexpr decltype(auto) getBuildinTypes(this Self& self) noexcept {
        using type = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&,
            T&>;

        if constexpr (trait_accessable<T, std::remove_pointer_t<TYPE_P>>) {
            if constexpr (SKIP > 0) {
                return self.template getBuildinTypes<SKIP - 1, REST_P...>();
            } else {
                return trait<std::remove_pointer_t<TYPE_P>>::get(static_cast<type>(self));
            }
        } else {
            return self.template getBuildinTypes<SKIP, REST_P...>();
        }
    }
    template <size_t SKIP, typename Self>
    constexpr decltype(auto) getBuildinTypes(this Self&) noexcept {}

    template <size_t SKIP, typename... TYPES_P, typename Self>
    constexpr decltype(auto) getBuildinTypes(this Self& self, std::variant<TYPES_P...>) noexcept {
        return self.template getBuildinTypes<SKIP, TYPES_P...>();
    }
};

namespace impl::Test {
using general_type = int;
using general_type2 = Name;

struct test_general_base {
    general_type type;
};

struct test_general_base2 {
    general_type2 type;
};

using tested_general_type = GeneralFeatures_<test_general_base>;
using tested_general_type2 = GeneralFeatures_<test_general_base2>;

static_assert(not have_all_get_features_for_type<tested_general_type, general_type>);  // ! general_type is not on list_of_types
static_assert(have_all_get_features_for_type<tested_general_type2, general_type2>);

}  // namespace impl::Test

}  // namespace impl

#include "Helpers/derived_from_property.hpp"

template <typename T>
using GeneralFeatures = impl::GeneralFeatures_<T>;
