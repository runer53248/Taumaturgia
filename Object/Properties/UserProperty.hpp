#pragma once
#include "../Concepts/Typeable.hpp"
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/UserStrategy.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char user_type_name[] = "UserProperty";

template <typename TYPE, typename T>
struct UserProperty_ : T {
    template <typename TAG>
    using self = UserProperty_<TYPE, TAG>;  // make yourself one template argument type to satisfy PropertyData
    using property_data = PropertyData<self, T, user_type_name>;

    UserProperty_() = default;

    // for ordered UserProperty_ (require name)

    template <typename... INFO>
        requires(std::is_constructible_v<TYPE, INFO...> and sizeof...(INFO) > 0)
    UserProperty_(const Name& name, std::tuple<INFO...>&& type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, type{std::move(std::make_from_tuple<TYPE>(std::forward<decltype(type)>(type)))} {}

    UserProperty_(const Name& name)
        : T{name} {}

    UserProperty_(const Name& name, [[maybe_unused]] decltype(std::ignore) type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    UserProperty_(const Name& name, TYPE&& type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, type{std::move(type)} {}

    UserProperty_(const Name& name, const TYPE& type, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, type{type} {}

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

    template <typename RETURN>
    decltype(auto) getType() & {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            return getType();
        } else if constexpr (GetTypeable<T, RETURN>) {
            return T::template getType<RETURN>();
        }
    }

    template <typename RETURN>
    decltype(auto) getType() const& {
        if constexpr (std::is_same_v<RETURN, TYPE>) {
            return getType();
        } else if constexpr (GetTypeable<T, RETURN>) {
            return T::template getType<RETURN>();
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

template <typename TYPE, typename T>
using UserProperty = std::conditional_t<Typeable<T, TYPE>, T, impl::UserProperty_<TYPE, T>>;

template <typename TYPE, typename T>
struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
