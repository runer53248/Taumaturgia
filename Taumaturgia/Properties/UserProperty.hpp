#pragma once
#include <boost/mp11.hpp>
#include <stdexcept>
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Strategies/UserStrategy.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "unordered_token.hpp"

namespace impl {
inline constinit const char user_type_name[] = "UserProperty";

template <typename T, typename TYPE, typename... Tags>
concept get_type_taged_able = requires {
    T::template getTypeTaged<TYPE, Tags...>();
};

// MARK: UserProperty_

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

// MARK: UserProperty_ for tag

template <typename TYPE /*, typename... Tags*/>
class UserProperty_<TYPE, tag /*, Tags...*/> {
public:
    template <typename TAG>
    using self = UserProperty_<TYPE, TAG /*, Tags...*/>;            // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<user_type_name, self, tag>;  // ? should add TYPE into PropertyData?
    using improvement_of = self<tag>;                               // will act like same type if TYPE and Tags are same

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() & noexcept {
        return (type_);
    }

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() const& noexcept {
        return (type_);
    }

private:
    TYPE type_{};
};

// MARK: UserProperty_ for T

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_ : public T {
public:
    template <typename TARGET>
    using self = UserProperty_<TYPE, TARGET, Tags...>;                     // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<user_type_name, self, T, Tags...>;  // ? should add TYPE into PropertyData?
    using improvement_of = self<T>;                                        // will act like same type if TYPE and Tags are same
    // using hold_type = TYPE;                                                // unused

    // template <typename TARGET>
    // using apply = std::conditional_t<
    //     trait_accessable<TARGET, TYPE>,
    //     TARGET,
    //     UserProperty_<TYPE, TARGET, Tags...>>;  // will act like same type if TYPE and Tags are same

    // MARK: Namingable tuple C-tors

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    UserProperty_(const Name& name, std::tuple<INFO...>&& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(std::move(type))} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    UserProperty_(const Name& name, const std::tuple<INFO...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(type)} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    // MARK: Namingable default and ignore C-tors

    UserProperty_(const Name& name)
        requires(not std::is_same_v<TYPE, Name> and std::constructible_from<T, Name>)
        : T{name} {}

    template <typename... Args>
    UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    UserProperty_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit UserProperty_(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: Namingable type C-tors

    template <typename... Args>
    UserProperty_(const Name& name, TYPE&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    UserProperty_(const Name& name, const TYPE& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{type} {}

    // MARK: Namingable variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<TYPE, V...> /*and Namingable<T>*/
    UserProperty_(const Name& name, const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...> /*and Namingable<T>*/
    UserProperty_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: tuple C-tors

    template <typename... INFO, typename... Args>
    constexpr UserProperty_(std::tuple<INFO...>&& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(std::move(type))} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
    constexpr UserProperty_(const std::tuple<INFO...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(type)} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    // MARK: default and ignore C-tors

    constexpr UserProperty_() = default;

    template <typename... Args>
    constexpr UserProperty_([[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: type C-tors

    template <typename... Args>
    constexpr UserProperty_(TYPE&& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr UserProperty_(const TYPE& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{type} {}

    // MARK: variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<TYPE, V...>
    UserProperty_(const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...>
    UserProperty_([[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: getType

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return (type_);
        } else {
            if constexpr (getType_template_able<T, RETURN>) {
                return T::template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return (type_);
        } else {
            if constexpr (getType_template_able<T, RETURN>) {
                return T::template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }

    // MARK: getTypeTaged

    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeTaged() & noexcept {
        if constexpr (std::same_as<
                          list<RETURN, TTags...>,
                          list<TYPE, Tags...>>) {
            return (type_);
        } else if constexpr (get_type_taged_able<T, RETURN, TTags...>) {
            return T::template getTypeTaged<RETURN, TTags...>();
        }
    }

    // MARK: getTypeLike

    template <
        typename RETURN,
        typename... TTags,
        template <typename, typename...> typename TT = list>
    constexpr decltype(auto) getTypeLike([[maybe_unused]] TT<RETURN, TTags...> type_structure) & noexcept {
        return getTypeTaged<RETURN, TTags...>();
    }

    template <typename TT>
    constexpr decltype(auto) getTypeLike() & noexcept {
        return getTypeLike(TT{});
    }

    // MARK: getTaged

    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() & noexcept {
        if constexpr (std::same_as<
                          list<TTags...>,
                          list<Tags...>>) {
            if constexpr (SKIP > 0) {
                return T::template getTaged<SKIP - 1, TTags...>();  // skip
            } else {
                return getTypeTaged<TYPE, TTags...>();  // return by tags and current type
            }
        } else {
            return T::template getTaged<SKIP, TTags...>();  // skip - diffrent tags
        }
    }

    template <typename... TTags>
    constexpr decltype(auto) getTaged() & noexcept {
        return getTaged<0, TTags...>();
    }

private:
    TYPE type_{};
};

}  // namespace impl

namespace impl::Test {
struct UserProperty_Test {};
static_assert(trait_accessable<UserProperty_<int, UserProperty_Test>, int>);
static_assert(trait_accessable<UserProperty_<int, tag>, int>);
}  // namespace impl::Test

#include "Helpers/derived_from_property.hpp"

template <typename TYPE, typename T, typename... Tags>
using UserProperty = std::conditional_t<
    trait_accessable<T, TYPE>,
    T,
    impl::UserProperty_<TYPE, T, Tags...>>;

template <typename TYPE, typename... Tags>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<TYPE, T, Tags...>;
};

template <typename TYPE, typename... Tags>
struct AdvanceUserProperty {
    template <typename T>
    using type = impl::UserProperty_<TYPE, T, Tags...>;

    template <typename T>
    using order = UserPropertyAdapter<TYPE, Tags...>::template type<T>;  // type valid for Property - pass is_property
};

template <typename TYPE, bool CONCEPT, typename... Tags>
struct UserPropertyConceptAdapter {
    template <typename T>
    using type = std::conditional_t<CONCEPT, T, UserProperty<TYPE, T, Tags...>>;
};

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
