#pragma once
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/CureHealth/CureHealth.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {

template <typename T>
class HealingSimple_ : public T {
public:
    using property_data = PropertyData<HealingSimple_, T>;
    using hold_type = CureHealth;
    using T::T;

    // MARK: Namingable type C-tors

    template <typename... Args>
    HealingSimple_(const Name& name, hold_type&& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, type_{std::move(cureHealth)} {}

    template <typename... Args>
    HealingSimple_(const Name& name, const hold_type& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, type_{cureHealth} {}

    // MARK: type C-tors

    template <typename... Args>
    HealingSimple_(hold_type&& cureHealth, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{std::move(cureHealth)} {}

    template <typename... Args>
    HealingSimple_(const hold_type& cureHealth, Args&&... args)
        : T{std::forward<Args>(args)...}, type_{cureHealth} {}

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit HealingSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    // MARK: getCureHealth

    constexpr auto& getCureHealth(this auto& self) {
        return self.type_;
    }

protected:
    hold_type type_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
