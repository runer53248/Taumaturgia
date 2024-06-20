#pragma once
#include <type_traits>
#include <utility>  // for as_const

namespace traits::helpers {
template <typename T, template <typename> typename CUSTOM_ACCESS, typename TYPE>
concept custom_trait_accessable = requires(std::remove_cvref_t<T> x) {
    { CUSTOM_ACCESS<std::remove_cvref_t<T>>::get(x) } -> std::same_as<TYPE&>;
    { CUSTOM_ACCESS<std::remove_cvref_t<T>>::get(std::as_const(x)) } -> std::same_as<const TYPE&>;
};

template <typename T, template <typename> typename CUSTOM_ACCESS, typename CONVERT_TYPE>
concept custom_trait_convertible = requires(std::remove_cvref_t<T> x) {
    { CUSTOM_ACCESS<std::remove_cvref_t<T>>::get(x) } -> std::convertible_to<CONVERT_TYPE>;
    { CUSTOM_ACCESS<std::remove_cvref_t<T>>::get(std::as_const(x)) } -> std::convertible_to<const CONVERT_TYPE>;
};

template <typename T, template <typename, typename> typename CUSTOM_ACCESS, typename TYPE>
concept custom_type_trait_accessable = requires(std::remove_cvref_t<T> x) {
    { CUSTOM_ACCESS<TYPE, std::remove_cvref_t<T>>::get(x) } -> std::same_as<TYPE&>;
    { CUSTOM_ACCESS<TYPE, std::remove_cvref_t<T>>::get(std::as_const(x)) } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE>
concept get_type_template_accessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE>() } -> std::same_as<TYPE&>;
    { std::as_const(x).template getType<TYPE>() } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE, typename CONVERT_TYPE>
concept get_type_template_convertible = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE>() } -> std::convertible_to<CONVERT_TYPE>;
    { std::as_const(x).template getType<TYPE>() } -> std::convertible_to<const CONVERT_TYPE>;
};
}  // namespace traits::helpers

#ifdef ACCESS_TRAIT_MACRO
#define CreateMemberAccessableConcept_convertible(NAME, MEMBER, TYPE) \
    template <typename T>                                             \
    concept NAME##Accessable = requires(T x) {                        \
        x.MEMBER;                                                     \
        requires std::is_convertible_v<decltype(T::MEMBER), TYPE>;    \
    };

#define CreateGetAccessableConcept_convertible(NAME, TYPE)                   \
    template <typename T>                                                    \
    concept Get##NAME##Accessable = requires(std::remove_cvref_t<T> x) {     \
        { x.get##NAME() } -> std::convertible_to<TYPE>;                      \
        { std::as_const(x).get##NAME() } -> std::convertible_to<const TYPE>; \
    };

#define CreateCustomAccessableConcept_convertible(NAME, TYPE) \
    template <typename T>                                     \
    struct CustomAccess##NAME;                                \
                                                              \
    template <typename T>                                     \
    concept Custom##NAME##Accessable = helpers::custom_trait_convertible<T, CustomAccess##NAME, TYPE>;

#define CreateUserTypeAccessableConcept_convertible(NAME, BUILD_TYPE, CONVERT_TYPE) \
    template <typename T>                                                           \
    concept UserType##NAME##Accessable = helpers::get_type_template_convertible<T, BUILD_TYPE, CONVERT_TYPE>;

#define CreateMemberAccessableConcept(NAME, MEMBER, TYPE) \
    template <typename T>                                 \
    concept NAME##Accessable = requires(T x) {            \
        x.MEMBER;                                         \
        std::is_same_v<decltype(T::MEMBER), TYPE>;        \
    };

#define CreateGetAccessableConcept(NAME, TYPE)                           \
    template <typename T>                                                \
    concept Get##NAME##Accessable = requires(std::remove_cvref_t<T> x) { \
        { x.get##NAME() } -> std::same_as<TYPE&>;                        \
        { std::as_const(x).get##NAME() } -> std::same_as<const TYPE&>;   \
    };

#define CreateCustomAccessableConcept(NAME, TYPE) \
    template <typename T>                         \
    struct CustomAccess##NAME;                    \
                                                  \
    template <typename T>                         \
    concept Custom##NAME##Accessable = helpers::custom_trait_accessable<T, CustomAccess##NAME, TYPE>;

#define CreateGetTypeTemplateAccessableConcept(NAME, TYPE) \
    template <typename T>                                  \
    concept GetTypeTemplate##NAME##Accessable = helpers::get_type_template_accessable<T, TYPE>;

#define CreateAccessTrait(NAME, MEMBER, TYPE)                                                  \
    struct access##NAME {                                                                      \
        static constexpr auto& get(NAME##Accessable auto& el) noexcept {                       \
            return el.MEMBER;                                                                  \
        }                                                                                      \
                                                                                               \
        template <Get##NAME##Accessable T>                                                     \
            requires(not(Custom##NAME##Accessable<T> or GetTypeTemplate##NAME##Accessable<T>)) \
        static constexpr decltype(auto) get(T& el) noexcept {                                  \
            return el.get##NAME();                                                             \
        }                                                                                      \
                                                                                               \
        template <Custom##NAME##Accessable T>                                                  \
            requires(not GetTypeTemplate##NAME##Accessable<T>)                                 \
        static constexpr decltype(auto) get(T& el) noexcept {                                  \
            return CustomAccess##NAME<std::remove_cvref_t<T>>::get(el);                        \
        }                                                                                      \
                                                                                               \
        template <GetTypeTemplate##NAME##Accessable T>                                         \
        static constexpr decltype(auto) get(T& el) noexcept {                                  \
            return el.template getType<TYPE>();                                                \
        }                                                                                      \
    };
#endif
