#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Health/Health.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {

template <typename T>
class LivingSimple_ : public T {
public:
    using property_data = PropertyData<LivingSimple_, T>;
    using hold_type = Health;
    using T::T;

    // MARK: Namingable type C-tors

    template <typename... Args>
    LivingSimple_(const Name& name, hold_type&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::move(hp)} {}

    template <typename... Args>
    LivingSimple_(const Name& name, const hold_type& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{hp} {}

    // MARK: type C-tors

    template <typename... Args>
    LivingSimple_(hold_type&& hp, Args&&... args)
        : T{std::forward<Args>(args)...}, hp_{std::move(hp)} {}

    template <typename... Args>
    LivingSimple_(const hold_type& hp, Args&&... args)
        : T{std::forward<Args>(args)...}, hp_{hp} {}

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit LivingSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: getHealth

    constexpr auto& getHealth(this auto& self) {
        return self.hp_;
    }

private:
    hold_type hp_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
