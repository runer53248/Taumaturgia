#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "../Concepts/Typeable.hpp"
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/UserStrategy.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char user_type_name[] = "UserProperty";

template <typename TYPE, typename T, typename... Args>
struct UserProperty_ : T {
    template <typename TAG>
    using self = UserProperty_<TYPE, TAG, Args...>;  // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<user_type_name, self, T>;
#ifdef USER_PROPERTY_SELF_AWARE
    using improvement_of = self<T>;
#endif

    UserProperty_() = default;

    // for ordered UserProperty_ (require name)

    template <typename... INFO>
        requires(std::is_constructible_v<TYPE, INFO...> and sizeof...(INFO) > 0)
    UserProperty_(const Name& name, std::tuple<INFO...>&& type, auto&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<decltype(args)>(args)...}, type{std::move(std::make_from_tuple<TYPE>(std::forward<decltype(type)>(type)))} {}

    UserProperty_(const Name& name)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name} {}

    UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, auto&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<decltype(args)>(args)...} {}

    UserProperty_(const Name& name, TYPE&& type, auto&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<decltype(args)>(args)...}, type{std::move(type)} {}

    UserProperty_(const Name& name, const TYPE& type, auto&&... args)
        requires(not std::is_same_v<TYPE, Name>)
        : T{name, std::forward<decltype(args)>(args)...}, type{type} {}

    template <typename... V>
        requires(boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const Name& name, const std::variant<V...>& type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, type{std::get<TYPE>(type)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const Name& name, [[maybe_unused]] const std::variant<V...>& type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    // for unordered UserProperty_ (can exist before TYPE accuire name property)

    template <typename... INFO>
        requires(std::is_constructible_v<TYPE, INFO...> and sizeof...(INFO) > 0)
    UserProperty_(std::tuple<INFO...>&& type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...}, type{std::move(std::make_from_tuple<TYPE>(std::forward<decltype(type)>(type)))} {}

    UserProperty_([[maybe_unused]] decltype(std::ignore) type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...} {}

    UserProperty_(TYPE&& type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...}, type{std::move(type)} {}

    UserProperty_(const TYPE& type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...}, type{type} {}

    template <typename... V>
        requires(boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_(const std::variant<V...>& type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...}, type{std::get<TYPE>(type)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, TYPE>::value and (sizeof...(V) > 0))
    UserProperty_([[maybe_unused]] const std::variant<V...>& type, auto&&... args)
        : T{std::forward<decltype(args)>(args)...} {}

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

template <typename TYPE, typename T>
struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
