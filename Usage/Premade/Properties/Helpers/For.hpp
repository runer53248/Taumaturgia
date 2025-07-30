#pragma once

namespace impl {

template <template <typename, typename...> typename property, typename... Tags>
struct For {
    template <typename TARGET>
    using type = property<TARGET, Tags...>;
};

}  // namespace impl
