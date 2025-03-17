#pragma once
#include <boost/mp11.hpp>
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

// MARK: GeneralFeatures_

template <typename T>
// requires(not std::is_reference_v<T>)
class GeneralFeatures_;

struct FeaturesFor {
    template <typename TARGET>
    using type = GeneralFeatures_<TARGET>;
};

// MARK: GeneralFeatures_ for T

template <typename T>
// requires(not std::is_reference_v<T>)
class GeneralFeatures_ : public T {
public:
    using property_data = PropertyData<general_features_name,
                                       FeaturesFor::template type,
                                       T>;       // ? should add TYPE into PropertyData?
    using improvement_of = GeneralFeatures_<T>;  // will act like same type if TYPE and Tags are same

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

    template <typename RETURN, size_t DIG = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (trait<RETURN>::template accessable<T>) {
            return trait<RETURN>::get(static_cast<T&>(*this));
        } else if constexpr (getType_template_able<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        } else {
            static_assert(false, "WARNING: getType method tries to return void type");
        }
    }

    template <typename RETURN, size_t DIG = 0>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (trait<RETURN>::template accessable<T>) {
            return trait<RETURN>::get(static_cast<const T&>(*this));
        } else if constexpr (getType_template_able<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        } else {
            static_assert(false, "WARNING: getType method tries to return void type");
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
        }
    }
    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
        if constexpr (get_taged_able<T, SKIP, TTags...>) {
            return T::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
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

#include "Helpers/derived_from_property.hpp"

template <typename T>
using GeneralFeatures = impl::GeneralFeatures_<T>;
