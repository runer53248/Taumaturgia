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
inline constinit const char user_type_name[] = "UserProperty";

template <typename T, typename TYPE, typename... Tags>
concept get_type_taged_able = requires {
    T::template getTypeTaged<TYPE, Tags...>();
};

// MARK: UserProperty_

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename TYPE, typename... Tags>
struct PropertyFor {
    template <typename TARGET>
    using type = UserProperty_<TYPE, TARGET, Tags...>;
};

// MARK: UserProperty_ for tag

template <typename TYPE /*, typename... Tags*/>
class UserProperty_<TYPE, tag /*, Tags...*/> {
public:
    using property_data = PropertyData<user_type_name,
                                       PropertyFor<TYPE /*, Tags...*/>::template type,
                                       tag>;                        // ? should add TYPE into PropertyData?
    using improvement_of = UserProperty_<TYPE, tag /*, Tags...*/>;  // will act like same type if TYPE and Tags are same
    using hold_type = TYPE;

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
    using property_data = PropertyData<user_type_name,
                                       PropertyFor<TYPE, Tags...>::template type,
                                       T,
                                       Tags...>;             // ? should add TYPE into PropertyData?
    using improvement_of = UserProperty_<TYPE, T, Tags...>;  // will act like same type if TYPE and Tags are same
    using hold_type = TYPE;

    // MARK: Namingable tuple C-tors

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    constexpr UserProperty_(const Name& name, std::tuple<INFO...>&& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(std::move(type))} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not std::is_same_v<TYPE, Name>)
    constexpr UserProperty_(const Name& name, const std::tuple<INFO...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::make_from_tuple<TYPE>(type)} {
        static_assert(constructible_from_args<TYPE, INFO...>, "Can't create TYPE from given tuple.");
    }

    // MARK: Namingable default and ignore C-tors

    constexpr UserProperty_(const Name& name)
        requires(not std::is_same_v<TYPE, Name> and std::constructible_from<T, Name>)
        : T{name} {}

    template <typename... Args>
    constexpr UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    constexpr UserProperty_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    constexpr explicit UserProperty_(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: Namingable type C-tors

    template <typename... Args>
    constexpr UserProperty_(const Name& name, TYPE&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{std::move(type)} {}

    template <typename... Args>
    constexpr UserProperty_(const Name& name, const TYPE& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type_{type} {}

    // MARK: Namingable variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<TYPE, V...> /*and Namingable<T>*/
    constexpr UserProperty_(const Name& name, const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...> /*and Namingable<T>*/
    constexpr UserProperty_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)
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
    constexpr UserProperty_(const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type_{std::get_if<TYPE>(&type)
                    ? std::get<TYPE>(type)
                    : TYPE{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<TYPE, V...>
    constexpr UserProperty_([[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    // MARK: getType

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            } else {
                return (type_);
            }
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
            } else {
                return (type_);
            }
        } else {
            if constexpr (getType_template_able<T, RETURN>) {
                return T::template getType<RETURN, DIG>();
            } else {
                // static_assert(false, "WARNING: getType method tries to return void type");
            }
        }
    }

    template <size_t DIG>
    constexpr decltype(auto) getType() & noexcept {
        if constexpr (DIG) {
            return T::template getType<DIG - 1>();
        } else {
            return (type_);
        }
    }

    template <size_t DIG>
    constexpr decltype(auto) getType() const& noexcept {
        if constexpr (DIG) {
            return T::template getType<DIG - 1>();
        } else {
            return (type_);
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
    template <typename RETURN, typename... TTags>
    constexpr decltype(auto) getTypeTaged() const& noexcept {
        if constexpr (std::same_as<
                          list<RETURN, TTags...>,
                          list<TYPE, Tags...>>) {
            return (type_);
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
    template <size_t SKIP, typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
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
    template <typename... TTags>
    constexpr decltype(auto) getTaged() const& noexcept {
        return getTaged<0, TTags...>();
    }

private:
    TYPE type_ = UserDefaultValue<TYPE, Tags...>::value();  // specialization for default values
};

}  // namespace impl

namespace impl::Test {
struct UserProperty_Test {};
using type = int;
using tested_type = UserProperty_<type, UserProperty_Test>;
using tested_tag = UserProperty_<type, tag>;

static_assert(trait_accessable<tested_type, type>);
static_assert(trait_accessable<tested_tag, type>);

static_assert(traits::helpers::trait_accessable<tested_type, trait<type>, type>);
static_assert(traits::helpers::GetTypeAccessable<tested_type, type>);

static_assert(requires(std::remove_cvref_t<tested_type> x) {  // same as traits::GetTypeAccessable<tested_type, type>
    { x.getType() } -> std::same_as<type&>;
    { std::as_const(x).getType() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getType<type>() } -> std::same_as<type&>;
    { std::as_const(x).getType<type>() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTypeTaged<type>() } -> std::same_as<type&>;
    { std::as_const(x).getTypeTaged<type>() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTypeTaged<type>() } -> std::same_as<type&>;
    { std::as_const(x).getTypeTaged<type>() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTaged() } -> std::same_as<type&>;
    { std::as_const(x).getTaged() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTaged<0>() } -> std::same_as<type&>;
    { std::as_const(x).getTaged<0>() } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTypeOf(list<type>{}) } -> std::same_as<type&>;
    { std::as_const(x).getTypeOf(list<type>{}) } -> std::same_as<const type&>;
});
static_assert(requires(std::remove_cvref_t<tested_type> x) {
    { x.getTypeOfSignature<list<type>>() } -> std::same_as<type&>;
    { std::as_const(x).getTypeOfSignature<list<type>>() } -> std::same_as<const type&>;
});

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

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
