#pragma once
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"

namespace impl {

// MARK: Constructors_

template <typename T>
class Constructors_ : public T {
public:
    using property_data = T::property_data;
    using T::T;
    using typename T::hold_type;

    Constructors_() = default;

    // MARK: Namingable tuple C-tors

    template <typename... INFO, typename... Args>
        requires std::constructible_from<T, const Name&, hold_type&&, Args&&...>
    Constructors_(const Name& name, std::tuple<INFO...>&& type, Args&&... args)
        : T{name, std::make_from_tuple<hold_type>(std::move(type)), std::forward<Args>(args)...} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create hold_type from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires std::constructible_from<T, const Name&, const hold_type&, Args&&...>
    Constructors_(const Name& name, const std::tuple<INFO...>& type, Args&&... args)
        : T{name, std::make_from_tuple<hold_type>(type), std::forward<Args>(args)...} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create hold_type from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Constructors_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: Namingable default

    Constructors_(const Name& name)
        : T{name} {}

    // MARK: Namingable ignore C-tors

    template <typename... Args>
        requires std::constructible_from<T, const Name&, Args&&...>
    Constructors_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: Namingable variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<hold_type, V...>  //
                 and std::constructible_from<T, const Name&, hold_type, Args&&...>
    Constructors_(const Name& name, const std::variant<V...>& type, Args&&... args)
        : T{name,
            std::get_if<hold_type>(&type)
                ? std::get<hold_type>(type)
                : hold_type{},
            std::forward<Args>(args)...} {}

    template <typename... V, typename... Args>
        requires not_contains_type<hold_type, V...>  //
                 and std::constructible_from<T, const Name&, Args&&...>
    Constructors_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)  // ! unused variant
        : T{name, std::forward<Args>(args)...} {}
};

}  // namespace impl
