#pragma once
#include <type_traits>

#define CreateAccessableConcept_convertible(NAME, MEMBER, TYPE)    \
    template <typename T>                                          \
    concept NAME##Accessable = requires(T x) {                     \
        x.MEMBER;                                                  \
        requires std::is_convertible_v<decltype(T::MEMBER), TYPE>; \
    };

#define CreateGetAccessableConcept_convertible(NAME, TYPE)                   \
    template <typename T>                                                    \
    concept Get##NAME##Accessable = requires(std::remove_cvref_t<T> x) {     \
        { x.get##NAME() } -> std::convertible_to<TYPE>;                      \
        { std::as_const(x).get##NAME() } -> std::convertible_to<const TYPE>; \
    };

#define CreateCustomAccessableConcept_convertible(NAME, TYPE)                                                     \
    template <typename T>                                                                                         \
    struct CustomAccess##NAME;                                                                                    \
                                                                                                                  \
    template <typename T>                                                                                         \
    concept Custom##NAME##Accessable = requires(std::remove_cvref_t<T> x) {                                       \
        { CustomAccess##NAME<std::remove_cvref_t<T>>::get(x) } -> std::convertible_to<TYPE>;                      \
        { CustomAccess##NAME<std::remove_cvref_t<T>>::get(std::as_const(x)) } -> std::convertible_to<const TYPE>; \
    };

#define CreateUserTypeAccessableConcept_convertible(NAME, BUILD_TYPE, CONVERT_TYPE)                     \
    template <typename T>                                                                               \
    concept UserType##NAME##Accessable = requires(std::remove_cvref_t<T> x) {                           \
        { x.template getType<BUILD_TYPE>() } -> std::convertible_to<CONVERT_TYPE>;                      \
        { std::as_const(x).template getType<BUILD_TYPE>() } -> std::convertible_to<const CONVERT_TYPE>; \
    };

#define CreateAccessableConcept(NAME, MEMBER, TYPE) \
    template <typename T>                           \
    concept NAME##Accessable = requires(T x) {      \
        x.MEMBER;                                   \
        std::is_same_v<decltype(T::MEMBER), TYPE>;  \
    };

#define CreateGetAccessableConcept(NAME, TYPE)                           \
    template <typename T>                                                \
    concept Get##NAME##Accessable = requires(std::remove_cvref_t<T> x) { \
        { x.get##NAME() } -> same_as_ref<TYPE>;                          \
        { std::as_const(x).get##NAME() } -> same_as_ref<const TYPE>;     \
    };

#define CreateCustomAccessableConcept(NAME, TYPE)                                    \
    template <typename T>                                                            \
    struct CustomAccess##NAME;                                                       \
                                                                                     \
    template <typename T>                                                            \
    concept Custom##NAME##Accessable = requires(std::remove_cvref_t<T> x) {          \
        { CustomAccess##NAME<T>::get(x) } -> same_as_ref<TYPE>;                      \
        { CustomAccess##NAME<T>::get(std::as_const(x)) } -> same_as_ref<const TYPE>; \
    };

#define CreateUserTypeAccessableConcept(NAME, TYPE)                               \
    template <typename T>                                                         \
    concept UserType##NAME##Accessable = requires(std::remove_cvref_t<T> x) {     \
        { x.template getType<TYPE>() } -> same_as_ref<TYPE>;                      \
        { std::as_const(x).template getType<TYPE>() } -> same_as_ref<const TYPE>; \
    };

#ifdef ACCESS_TRAIT_MACRO
#define CreateAccessTrait(NAME, MEMBER, TYPE)                                           \
    struct access##NAME {                                                               \
        static auto& get(NAME##Accessable auto& el) {                                   \
            return el.MEMBER;                                                           \
        }                                                                               \
                                                                                        \
        template <Get##NAME##Accessable T>                                              \
            requires(not(Custom##NAME##Accessable<T> or UserType##NAME##Accessable<T>)) \
        static decltype(auto) get(T& el) {                                              \
            return el.get##NAME();                                                      \
        }                                                                               \
                                                                                        \
        template <Custom##NAME##Accessable T>                                           \
            requires(not UserType##NAME##Accessable<T>)                                 \
        static decltype(auto) get(T& el) {                                              \
            return CustomAccess##NAME<std::remove_cvref_t<T>>::get(el);                 \
        }                                                                               \
                                                                                        \
        template <UserType##NAME##Accessable T>                                         \
        static decltype(auto) get(T& el) {                                              \
            return el.template getType<TYPE>();                                         \
        }                                                                               \
    };
#endif
