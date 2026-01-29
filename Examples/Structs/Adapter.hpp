#pragma once

template <template <typename...> typename property, isTag TAGS>
struct Adapter {
    template <typename T>
    using type = property<T, TAGS>;
};
