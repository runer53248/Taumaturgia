#pragma once
#include "../Concepts/Types/Name.hpp"
// #include "../Strategies/UserStrategy.hpp"
#include "../Concepts/UserTypeConcept.hpp"
#include "PropertyData.hpp"

constexpr char user_type_name[] = "UserType";

template <typename T, typename TYPE>
struct UserProperty_ : T {
    template <typename TT, typename TYPET = TYPE>
    using self = UserProperty_<TT, TYPET>;  // make yourself one template argument type
    using property_data = PropertyData<self, T, user_type_name>;

    UserProperty_() = default;

    // for ordered

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

    //for unordered

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

    auto& getType() {
        return type;
    }

    const auto& getType() const {
        return type;
    }

    template <typename N_TYPE>
    decltype(auto) getType() {
        if constexpr (std::is_same_v<N_TYPE, TYPE>) {
            return getType();
        } else {
            return T::template getType<N_TYPE>();
        }
        // return traits::accessUserType<N_TYPE>::get(*this);
    }

    template <typename N_TYPE>
    decltype(auto) getType() const {
        if constexpr (std::is_same_v<N_TYPE, TYPE>) {
            return getType();
        } else {
            return T::template getType<N_TYPE>();
        }
        // return traits::accessUserType<N_TYPE>::get(*this);
    }

private:
    TYPE type{};
};

namespace Test {
struct UserProperty_Test {};
static_assert(UserTypeConceptable<UserProperty_<UserProperty_Test, int>, int>);
}  // namespace Test

template <typename T, typename TYPE>
using UserProperty = std::conditional_t<UserTypeConceptable<T, TYPE>, T, UserProperty_<T, TYPE>>;

// template <typename T>
// struct UserStrategy_<UserProperty_<T>> : UserStrategy_<T> {};  // forward eventualy implemented strategy
