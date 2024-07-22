#pragma once
#include <boost/mp11.hpp>
#include <stdexcept>
#include <variant>
#include "Helpers/constructible_from_args.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Strategies/UserStrategy.hpp"
#include "Usage/Types/Name/Name.hpp"

struct Token {};

inline Token token{};

namespace impl {
inline constinit const char user_type_name[] = "UserProperty";

template <typename TYPE, typename T, typename... Tags>
class UserProperty_ : public T {
public:
    template <typename TAG>
    using self = UserProperty_<TYPE, TAG, Tags...>;                        // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<user_type_name, self, T, Tags...>;  // ? should add TYPE into PropertyData?
    using improvement_of = self<T>;                                        // will act like same type if TYPE and Tags are same
    // using hold_type = TYPE;  // unused

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
        requires(not std::is_same_v<TYPE, Name>)
        : T{name} {}

    template <typename... Args>
    UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    // !

    template <typename... Args>
    UserProperty_(const Token&, Args&&... args)
        : T{} {
        ((trait<Args>::get(*this) = std::forward<Args>(args)),...);
    }

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
    constexpr decltype(auto) getType() & {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return (type_);
        }
        if constexpr (getType_template_able<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        }
    }

    template <typename RETURN = TYPE, size_t DIG = 0>
    constexpr decltype(auto) getType() const& {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (getType_template_able<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return (type_);
        }
        if constexpr (getType_template_able<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        }
    }

private:
    TYPE type_{};
};

}  // namespace impl

namespace impl::Test {
struct UserProperty_Test {};
static_assert(traits::accessType<int>::accessable<UserProperty_<int, UserProperty_Test>>);
}  // namespace impl::Test

template <typename TYPE, typename T, typename... Args>
using UserProperty = std::conditional_t<
    traits::accessType<TYPE>::template accessable<T>,
    T,
    impl::UserProperty_<TYPE, T, Args...>>;

template <typename TYPE, typename... Args>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<TYPE, T, Args...>;
};

template <typename TYPE, bool CONCEPT, typename... Args>
struct UserPropertyConceptAdapter {
    template <typename T>
    using type = std::conditional_t<CONCEPT, T, UserProperty<TYPE, T, Args...>>;
};

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
