#pragma once
#include <stdexcept>
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Strategies/UserStrategy.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

namespace impl {
inline constinit const char general_features_name[] = "GeneralFeatures";

template <typename T, size_t SKIP, typename... Tags>
concept get_taged_able = requires {
    T::template getTaged<SKIP, Tags...>();
};

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

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    constexpr GeneralFeatures_(const Token&, Args&&... args)
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
    constexpr decltype(auto) getType(this Self& self) noexcept {
        using boost::mp11::mp_at_c;
        using boost::mp11::mp_filter;
        using boost::mp11::mp_size;
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
                 int>>;  // ! extra type int
        using TT = std::conditional_t<
            std::is_const_v<std::remove_reference_t<Self>>,
            const T&, T&>;
        if constexpr (DIG < mp_size<L>::value) {
            return trait<mp_at_c<L, DIG>>::get(static_cast<TT>(self));
        }
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeTaged() & noexcept {
        if constexpr (std::same_as<list<>, list<TTags...>>) {
            return getType<RETURN>();
        } else if constexpr (get_type_taged_able<T, RETURN, TTags...>) {
            return T::template getTypeTaged<RETURN, TTags...>();
        }
    }
    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeTaged() const& noexcept {
        if constexpr (std::same_as<list<>, list<TTags...>>) {
            return getType<RETURN>();
        } else if constexpr (get_type_taged_able<T, RETURN, TTags...>) {
            return T::template getTypeTaged<RETURN, TTags...>();
        }
    }

    // MARK: getTypeOf

    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeOf([[maybe_unused]] list<RETURN, TTags...> signature) & noexcept {
        return getTypeTaged<RETURN, TTags...>();
    }
    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeOf([[maybe_unused]] list<RETURN, TTags...> signature) const& noexcept {
        return getTypeTaged<RETURN, TTags...>();
    }

    // MARK: getTypeOfSignature

    template <typename Signature>
    constexpr decltype(auto) getTypeOfSignature() & noexcept {
        return getTypeOf(Signature{});
    }
    template <typename Signature>
    constexpr decltype(auto) getTypeOfSignature() const& noexcept {
        return getTypeOf(Signature{});
    }

    // MARK: getTaged

    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() & noexcept {
        if constexpr (get_taged_able<T, SKIP, TTags...>) {
            return T::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        } else if constexpr (std::same_as<list<>, list<TTags...>>) {
            return getBuildinTypes<SKIP>(types_ptr{});
        }
    }
    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
        if constexpr (get_taged_able<T, SKIP, TTags...>) {
            return T::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        } else if constexpr (std::same_as<list<>, list<TTags...>>) {
            return getBuildinTypes<SKIP>(types_ptr{});
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

private:
    template <class TT>
    using trait_accessable_fn = boost::mp11::mp_bool<trait_accessable<T, TT>>;

    template <size_t SKIP, typename TYPE_P, typename... REST_P>
    constexpr decltype(auto) getBuildinTypes() & noexcept {
        if constexpr (trait_accessable<T, std::remove_pointer_t<TYPE_P>>) {
            if constexpr (SKIP > 0) {
                return getBuildinTypes<SKIP - 1, REST_P...>();
            } else {
                return trait<std::remove_pointer_t<TYPE_P>>::get(static_cast<T&>(*this));
            }
        } else {
            return getBuildinTypes<SKIP, REST_P...>();
        }
    }
    template <size_t SKIP, typename TYPE_P, typename... REST_P>
    constexpr decltype(auto) getBuildinTypes() const& noexcept {
        if constexpr (trait_accessable<T, std::remove_pointer_t<TYPE_P>>) {
            if constexpr (SKIP > 0) {
                return getBuildinTypes<SKIP - 1, REST_P...>();
            } else {
                return trait<std::remove_pointer_t<TYPE_P>>::get(static_cast<const T&>(*this));
            }
        } else {
            return getBuildinTypes<SKIP, REST_P...>();
        }
    }
    template <size_t SKIP>
    constexpr decltype(auto) getBuildinTypes() & noexcept {}
    template <size_t SKIP>
    constexpr decltype(auto) getBuildinTypes() const& noexcept {}

    template <size_t SKIP, typename... TYPES_P>
    constexpr decltype(auto) getBuildinTypes(std::variant<TYPES_P...>) & noexcept {
        return getBuildinTypes<SKIP, TYPES_P...>();
    }

    template <size_t SKIP, typename... TYPES_P>
    constexpr decltype(auto) getBuildinTypes(std::variant<TYPES_P...>) const& noexcept {
        return getBuildinTypes<SKIP, TYPES_P...>();
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

static_assert(not have_get_features<tested_general_type, general_type>);  // ! general_type is not on list_of_types
static_assert(have_get_features<tested_general_type2, general_type2>);

}  // namespace impl::Test

}  // namespace impl

#include "Helpers/derived_from_property.hpp"

template <typename T>
using GeneralFeatures = impl::GeneralFeatures_<T>;
