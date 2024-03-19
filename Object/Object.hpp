#pragma once
#include <concepts>
#include <memory>
#include <optional>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

#include "Enums/ActionStatus.hpp"
#include "Enums/Actions.hpp"
#include "Enums/AliveStatus.hpp"

#include <experimental/propagate_const>
#include <functional>

class Object;

template <typename T>
concept Objected = std::same_as<T, Object> or std::same_as<T, const Object>;

class Object {
private:
    struct ObjectConcept {  // TODO: implement copy
    public:
        virtual constexpr ~ObjectConcept() = default;

        virtual constexpr std::string name() const = 0;
        virtual constexpr std::optional<AliveStatus> alive() const = 0;
        virtual constexpr ActionStatus action(Actions action, Object* owner, Object* target) const = 0;
        virtual constexpr get_optional_variant_type get(Parameter param) = 0;
        virtual constexpr get_optional_variant_const_type get(Parameter param) const = 0;
    };

    class Action_impl;

    template <Namingable T>
    struct ObjectModel : ObjectConcept {
    public:
        constexpr ObjectModel(const T& type);
        constexpr ~ObjectModel() override = default;

        constexpr std::string name() const override;
        constexpr std::optional<AliveStatus> alive() const override;
        constexpr ActionStatus action(Actions action, Object* owner, Object* target) const override;

        constexpr get_optional_variant_type get(Parameter param) override;
        constexpr get_optional_variant_const_type get(Parameter param) const override;

    private:
        T type_;
    };

    std::experimental::propagate_const<std::unique_ptr<ObjectConcept>> object_;

public:
    const bool can_alive{};
    const bool can_attack{};
    const bool can_defend{};
    const bool can_heal{};
    const bool can_restore{};
    const bool can_wear{};
    const bool can_get{};

    template <Namingable T>
    Object(const T& obj)
        : object_{std::make_unique<ObjectModel<T>>(obj)},
          can_alive{is_alive_strategy<T>},
          can_attack{is_attack_strategy<T>},
          can_defend{is_defend_strategy<T>},
          can_heal{is_heal_strategy<T>},
          can_restore{is_restore_strategy<T>},
          can_wear{is_wear_strategy<T>},
          can_get{is_get_strategy<T>} {}

    std::string name() const;
    std::optional<AliveStatus> alive() const;
    ActionStatus attack(Object* owner, Object* target = nullptr) const;
    ActionStatus defend(Object* owner, Object* target = nullptr) const;
    ActionStatus wear(Object* owner, Object* target = nullptr) const;
    ActionStatus heal(Object* owner, Object* target = nullptr) const;
    ActionStatus restore(Object* owner, Object* target = nullptr) const;

    template <Parameter param>
    bool checkGetParam() const;

    template <Parameter param>
    friend constexpr auto getOptVariant(Objected auto& object) {  // return type depends on object constness
        if (object.template checkGetParam<param>()) {
            return object.object_->get(param);  // return get_optional_variant_type or get_optional_variant_const_type
        }
        return decltype(object.object_->get(param)){};
    }

    template <Parameter param>
    friend constexpr auto getOpt(Objected auto& object) {
        auto opt_variant = getOptVariant<param>(object);
        return get_opt_ref_wrapper<param>(opt_variant);
    }
};

#include "ObjectModel.hpp"
