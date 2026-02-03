#pragma once
#include <concepts>


template <typename... TAGS>
struct Tags;

template <>
struct Tags<> {
    static constexpr auto size = 0;
};

template <typename... TAGS>
struct Tags : Tags<> {
    static constexpr auto size = sizeof...(TAGS);
};

template <typename T>
concept isTag = std::derived_from<T, Tags<>> or std::is_same_v<T, Tags<>>;

using no_tag = Tags<>;
