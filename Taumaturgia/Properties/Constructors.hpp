#pragma once
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

template <typename T, typename... Tags>
struct Data {
    T value;
};

template <typename... Tags, typename T>
decltype(auto) forTags(T&& data) {
    return Data<T, Tags...>{std::forward<T>(data)};
}

namespace impl {

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename T>
class Constructors;

template <typename TYPE, typename T, typename... Tags>
class Constructors<UserProperty_<TYPE, T, Tags...>> : public T {
public:
    using hold_type = TYPE;

    // MARK: Namingable tuple C-tors

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

    // MARK: Namingable default and ignore C-tors

    constexpr Constructors(const Name& name)
        requires(not std::is_same_v<TYPE, Name> and std::constructible_from<T, Name>)
        : T{name} {}

    template <typename... Args>
    constexpr Constructors(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: Unordered C-tors

    template <typename TT, typename... TTags>
    constexpr Constructors(const Unordered&, Data<TT, TTags...>&& arg) {
        using user_prop = UserProperty_<TYPE, T, Tags...>;

        getTypeTaged<TT, TTags...>(*static_cast<user_prop*>(this)) = arg.value;
    }

    template <typename TT, typename... TTags, typename... Args>
    constexpr Constructors(const Unordered& u, Data<TT, TTags...>&& arg, Args&&... args)
        : Constructors{u, std::forward<Args>(args)...} {
        using user_prop = UserProperty_<TYPE, T, Tags...>;

        getTypeTaged<TT, TTags...>(*static_cast<user_prop*>(this)) = arg.value;
    }

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    constexpr Constructors(const Unordered&, Args&&... args)
        : T{} {
        // using user_prop = Constructors<UserProperty_<TYPE, T, Tags...>>;
        using user_prop = UserProperty_<TYPE, T, Tags...>;

        constexpr bool have_all_types_from_args = (trait_accessable<user_prop, std::remove_cvref_t<Args>> and ...);
        if constexpr (have_all_types_from_args) {
            ((trait<std::remove_cvref_t<Args>>::get(*static_cast<user_prop*>(this)) = std::forward<Args>(args)), ...);
            // ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
        } else {
            static_assert(have_all_types_from_args, "Unordered c-tor arguments contains type not accessable by traits.");
        }
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    constexpr explicit Constructors(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: Namingable type C-tors

    template <typename... Args>
    constexpr Constructors(const Name& name, TYPE&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr Constructors(const Name& name, const TYPE& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{type} {}

    // MARK: Namingable variant C-tors

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

    // MARK: tuple C-tors

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

    // MARK: default and ignore C-tors

    constexpr Constructors() = default;

    template <typename... Args>
    constexpr Constructors([[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: type C-tors

    template <typename... Args>
    constexpr Constructors(TYPE&& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr Constructors(const TYPE& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{type} {}

    // MARK: variant C-tors

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

    // MARK: getT

    template <typename Self>
    constexpr decltype(auto) getT(this Self& self) {
        return (self.type_);
    }

private:
    hold_type type_ = UserDefaultValue<hold_type, Tags...>::value();  // specialization for default values
};

}  // namespace impl
