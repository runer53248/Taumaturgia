#pragma once
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "UserDefaultValue.hpp"
#include "unordered_token.hpp"

namespace impl {

// MARK: UserProperty_

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename TYPE, typename... Tags>
struct PropertyFor {
    template <typename TARGET>
    using type = UserProperty_<TYPE, TARGET, Tags...>;
};  // may be specialized to replacing UserProperty_

template <typename T, typename Base, size_t DIG>
concept parent_digingable = requires(T t) {
    static_cast<const Base&>(t).template getType<DIG - 1>();
};

// MARK: UserProperty_ for T

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_ : public T {
public:
    using property_data = PropertyData<PropertyFor<TYPE, Tags...>::template type,
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

    // MARK: Unordered C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    constexpr UserProperty_(const Unordered&, Args&&... args)
        : T{} {
        constexpr bool have_all_types_from_args = (trait_accessable<UserProperty_<TYPE, T, Tags...>, std::remove_cvref_t<Args>> and ...);
        if constexpr (have_all_types_from_args) {
            ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
        } else {
            static_assert(have_all_types_from_args, "Unordered c-tor arguments contains type not accessable by traits.");
        }
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
        requires have_getType_type_num<improvement_of, RETURN, NUM>
    static consteval bool haveTypeNum() noexcept {
        return true;
    }
    template <typename RETURN = TYPE, size_t NUM = 0>
    static consteval bool haveTypeNum() noexcept {
        return false;
    }

    template <size_t NUM>
        requires have_getType_num<improvement_of, NUM>
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
        return (self.type_);
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
        requires(not get_type_taged_able<T, RETURN, TTags...>  //
                 and not std::same_as<list<RETURN, TTags...>, list<TYPE, Tags...>>)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;

    // MARK: getTypeOf

    template <typename RETURN, typename... TTags, typename Self>
        requires get_type_taged_able<Self, RETURN, TTags...>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept {
        return self.template getTypeTaged<RETURN, TTags...>();
    }

    template <typename RETURN, typename... TTags, typename Self>
    constexpr decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTags...> signature) noexcept = delete;

    // MARK: getTypeOfSignature

    template <typename Signature, typename Self>
        requires requires(Self s) { s.getTypeOf(Signature{}); }
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
        } else if constexpr (get_type_taged_able<Self, TYPE, TTags...>) {
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

static_assert(getType_able<tested_type, type>);

static_assert(have_get_features<tested_type, type>);

}  // namespace impl::Test

#include "Helpers/derived_from_property.hpp"

template <typename TYPE, typename T, typename... Tags>
using UserProperty = std::conditional_t<
    (trait_accessable<T, TYPE> and  //
     (is_getTypeTags_valid<T, TYPE, Tags...>)),
    T,
    impl::UserProperty_<TYPE, T, Tags...>>;

template <typename TYPE, typename... Tags>
struct UserPropertyAdapter {
    template <typename T>
    using apply = impl::UserProperty_<TYPE, T, Tags...>;

    template <typename T>
    using once = UserProperty<TYPE, T, Tags...>;
};

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
