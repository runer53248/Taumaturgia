#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Helpers/PropertyData.hpp"
#include "Helpers/constructible_from_args.hpp"
#include "Object/Concepts/Typeable.hpp"
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/UserStrategy.hpp"

namespace impl {
constinit char user_type_name[] = "UserProperty";

template <typename TYPE, typename T, typename... Tags>
struct UserProperty_ : T {
    template <typename TAG>
    using self = UserProperty_<TYPE, TAG, Tags...>;                        // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<user_type_name, self, T, Tags...>;  // ? should add TYPE into PropertyData?
#ifdef USER_PROPERTY_SELF_AWARE
    using improvement_of = self<T>;  // will act like same type if TYPE and Tags are same
#endif
    using hold_type = TYPE;  // unused

    UserProperty_() = default;

    // for ordered UserProperty_ (require T have name property)

    template <typename... INFO, typename... Args>
    UserProperty_(const Name& name, std::tuple<INFO...>&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...},
          type{std::make_from_tuple<TYPE>(std::move(type))} {}

    template <typename... INFO, typename... Args>
    UserProperty_(const Name& name, const std::tuple<INFO...>& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...},
          type{std::make_from_tuple<TYPE>(type)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<TYPE, INFO...>)
    UserProperty_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<TYPE, INFO...>)
    UserProperty_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create TYPE from given tuple.");
    }

    UserProperty_(const Name& name)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name} {}

    template <typename... Args>
    UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    UserProperty_(const Name& name, TYPE&& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type{std::move(type)} {}

    template <typename... Args>
    UserProperty_(const Name& name, const TYPE& type, Args&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<Args>(args)...}, type{type} {}

    template <typename... V, typename... Args>
        requires(boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const Name& name, const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...}, type{std::get<TYPE>(type)} {}

    template <typename... V, typename... Args>
        requires(not boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // for unordered UserProperty_ (can exist before T accuire name property)

    template <typename... INFO, typename... Args>
    UserProperty_(std::tuple<INFO...>&& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type{std::make_from_tuple<TYPE>(std::move(type))} {}

    template <typename... INFO, typename... Args>
    UserProperty_(const std::tuple<INFO...>& type, Args&&... args)
        : T{std::forward<Args>(args)...},
          type{std::make_from_tuple<TYPE>(type)} {}

    template <typename... INFO,  typename... Args>
        requires(not constructible_from_args<TYPE, INFO...>)
    UserProperty_(std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create TYPE from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<TYPE, INFO...>)
    UserProperty_(const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create TYPE from given tuple.");
    }

    template <typename... Args>
    UserProperty_([[maybe_unused]] decltype(std::ignore) type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    template <typename... Args>
    UserProperty_(TYPE&& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type{std::move(type)} {}

    template <typename... Args>
    UserProperty_(const TYPE& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type{type} {}

    template <typename... V, typename... Args>
        requires(boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...}, type{std::get<TYPE>(type)} {}

    template <typename... V, typename... Args>
        requires(not boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_([[maybe_unused]] const std::variant<V...>& type, Args&&... args)
        : T{std::forward<Args>(args)...} {}

    template <typename RETURN, int DIG = 0>
    decltype(auto) getType() & {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (GetTypeable<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return getType();
        }
        if constexpr (GetTypeable<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        }
    }

    template <typename RETURN, int DIG = 0>
    decltype(auto) getType() const& {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            if constexpr (DIG) {
                if constexpr (GetTypeable<T, RETURN>) {
                    return T::template getType<RETURN, DIG - 1>();
                }
            }
            return getType();
        }
        if constexpr (GetTypeable<T, RETURN>) {
            return T::template getType<RETURN, DIG>();
        }
    }

protected:
    auto& getType() & {
        return type;
    }

    const auto& getType() const& {
        return type;
    }

private:
    TYPE type{};
};

namespace Test {
struct UserProperty_Test {};
static_assert(Typeable<UserProperty_<int, UserProperty_Test>, int>);
}  // namespace Test

}  // namespace impl

template <typename TYPE, typename T, typename... Args>
using UserProperty = std::conditional_t<Typeable<T, TYPE>, T, impl::UserProperty_<TYPE, T, Args...>>;

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

template <typename TYPE, typename T>
struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
