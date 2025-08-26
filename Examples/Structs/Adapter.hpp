#pragma once

template <template <typename...> typename property, typename... Tags>
struct Adapter {
    template <typename T>
    using type = property<T, Tags...>;
};
