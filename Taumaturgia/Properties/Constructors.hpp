#pragma once
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

template <typename T, isTag TAGS>
struct Data {
    T value;
};

template <isTag TAGS = no_tag, typename T>
constexpr decltype(auto) forTags(T&& data) {
    return Data<T, TAGS>{std::forward<T>(data)};
}

namespace impl {

template <typename TYPE, typename T, isTag TAGS>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename T>
class Constructors;

template <typename TYPE, typename T, isTag TAGS>
class Constructors<UserProperty_<TYPE, T, TAGS>> : public T {
public:
    using hold_type = TYPE;

    // MARK: Namingable tuple

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    constexpr Constructors(const Name& name, std::tuple<INFO...>&& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(std::move(type))} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    constexpr Constructors(const Name& name, const std::tuple<INFO...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(type)} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    // MARK: Namingable default and ignore

    constexpr Constructors(const Name& name)
        requires(not std::is_same_v<TYPE, Name> and std::constructible_from<T, Name>)
        : T{name} {}

    template <typename... Args>
    constexpr Constructors(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: Unordered Data<>

    template <typename TT, isTag TTAGS>
    constexpr Constructors(const Unordered&, Data<TT, TTAGS>&& arg) {
        using user_prop = UserProperty_<TYPE, T, TAGS>;
        using type_TT = std::remove_cvref_t<TT>;

        getTypeTaged<type_TT, TTAGS>(*static_cast<user_prop*>(this)) = arg.value;
    }

    template <typename TT, isTag TTAGS, typename... Args>
    constexpr Constructors(const Unordered& u, Data<TT, TTAGS>&& arg, Args&&... args)
        : Constructors{u, std::forward<Args>(args)...} {
        using user_prop = UserProperty_<TYPE, T, TAGS>;
        using type_TT = std::remove_cvref_t<TT>;

        getTypeTaged<type_TT, TTAGS>(*static_cast<user_prop*>(this)) = arg.value;
    }

    template <typename TT, isTag TTAGS, typename... Args>
        requires(not std::same_as<
                    boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>,
                    list<std::remove_cvref_t<Args>...>>)  // arguments are not of unique type
    constexpr Constructors(const Unordered& u, Data<TT, TTAGS>&& arg, Args&&... args) = delete;

    // MARK: Unordered

    template <typename Arg>
    constexpr Constructors(const Unordered&, Arg&& arg) {
        using user_prop = UserProperty_<TYPE, T, TAGS>;
        using type_Arg = std::remove_cvref_t<Arg>;

        if constexpr (requires { getTypeTaged<type_Arg, no_tag>(*static_cast<user_prop*>(this)); }) {
            getTypeTaged<type_Arg, no_tag>(*static_cast<user_prop*>(this)) = std::forward<Arg>(arg);
        } else if constexpr (trait_accessable<user_prop, type_Arg>) {
            trait<type_Arg>::get(*static_cast<user_prop*>(this)) = std::forward<Arg>(arg);
        } else {
            static_assert(false, "Unordered c-tor arguments contains type not accessable by traits.");
        }
    }

    template <typename Arg, typename... Args>
    constexpr Constructors(const Unordered& u, Arg&& arg, Args&&... args)
        : Constructors{u, std::forward<Args>(args)...} {
        using user_prop = UserProperty_<TYPE, T, TAGS>;
        using type_Arg = std::remove_cvref_t<Arg>;

        if constexpr (requires { getTypeTaged<type_Arg, no_tag>(*static_cast<user_prop*>(this)); }) {
            getTypeTaged<type_Arg, no_tag>(*static_cast<user_prop*>(this)) = std::forward<Arg>(arg);
        } else if constexpr (trait_accessable<user_prop, type_Arg>) {
            trait<type_Arg>::get(*static_cast<user_prop*>(this)) = std::forward<Arg>(arg);
        } else {
            static_assert(false, "Unordered c-tor arguments contains type not accessable by traits.");
        }
    }

    template <typename Arg, typename... Args>
        requires(not std::same_as<
                    boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>,
                    list<std::remove_cvref_t<Args>...>>)  // arguments are not of unique type
    constexpr Constructors(const Unordered& u, Arg&& arg, Args&&... args) = delete;

    // MARK: copy/move

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    constexpr explicit Constructors(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: Namingable type

    template <typename... Args>
    constexpr Constructors(const Name& name, TYPE&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr Constructors(const Name& name, const TYPE& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{type} {}

    // MARK: Namingable variant

    template <typename... V, typename... Args>
        requires contains_type<TYPE, V...> /*and Namingable<T>*/
    constexpr Constructors(const Name& name, const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...> /*and Namingable<T>*/
    constexpr Constructors(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: tuple

    template <typename... INFO, typename... Args>
    constexpr Constructors(std::tuple<INFO...>&& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(std::move(type))} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
    constexpr Constructors(const std::tuple<INFO...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(type)} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    // MARK: default and ignore

    constexpr Constructors() = default;

    template <typename... Args>
    constexpr Constructors([[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: type

    template <typename... Args>
    constexpr Constructors(TYPE&& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr Constructors(const TYPE& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{type} {}

    // MARK: variant

    template <typename... V, typename... Args>
        requires contains_type<TYPE, V...>
    constexpr Constructors(const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...>
    constexpr Constructors([[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...} {}  //? skip type

protected:
    hold_type type_ = UserDefaultValue<hold_type, TAGS>::value();  // specialization for default values
};

}  // namespace impl
