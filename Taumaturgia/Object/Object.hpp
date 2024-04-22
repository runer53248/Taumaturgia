#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include "Enums/Actions.hpp"
#include "Enums/ActionStatus.hpp"
#include "Taumaturgia/Concepts/Namingable.hpp"
#include "Taumaturgia/Strategies/Strategies.hpp"

#ifndef _MSC_VER
#include <experimental/propagate_const>
#endif

#include "Command.hpp"

class Object;

template <typename T>
concept is_object = std::same_as<T, Object> or std::same_as<T, const Object>;

class Object {
private:
    class ObjectConcept {  // TODO: implement copy
    public:
        virtual constexpr ~ObjectConcept() = default;

        virtual constexpr std::string name() const = 0;
        virtual constexpr std::optional<AliveStatus> alive() const = 0;
        virtual constexpr ActionStatus action(Actions action, Object* owner, Object* target) const = 0;
        virtual constexpr optional_get_variant_type get(Properties param) = 0;
        virtual constexpr optional_get_variant_const_type get(Properties param) const = 0;
    };

    template <Namingable T>
    class ObjectModel : public ObjectConcept {
    public:
        constexpr ObjectModel(const T& type);
        constexpr ~ObjectModel() override = default;

        constexpr std::string name() const override;
        constexpr std::optional<AliveStatus> alive() const override;
        constexpr ActionStatus action(Actions action, Object* owner, Object* target) const override;
        constexpr optional_get_variant_type get(Properties param) override;
        constexpr optional_get_variant_const_type get(Properties param) const override;

    private:
        T type_;
        std::unordered_map<Actions, std::shared_ptr<CommandConcept>> commands_;
    };

#ifndef _MSC_VER
    std::experimental::propagate_const<std::unique_ptr<ObjectConcept>> object_;
#else
    std::unique_ptr<ObjectConcept> object_;
#endif
    const std::unordered_map<Properties, const bool> has;

    ActionStatus doAction(Actions action, Object* owner, Object* target) const;

public:
    template <Namingable T>
    Object(const T& obj)
        : object_{std::make_unique<ObjectModel<T>>(obj)},
          has{{Properties::Health, is_alive_strategy<T>},
              {Properties::CureHealth, is_heal_strategy<T>},
              {Properties::Protection, is_defend_strategy<T>},
              {Properties::Damage, is_attack_strategy<T>},
              {Properties::Restore, is_restore_strategy<T>},
              {Properties::Wear, is_wear_strategy<T>},
              {Properties::Get, is_get_strategy<T>}} {}

    std::string name() const;
    std::optional<AliveStatus> alive() const;
    ActionStatus attack(Object* owner, Object* target = nullptr) const;
    ActionStatus defend(Object* owner, Object* target = nullptr) const;
    ActionStatus wear(Object* owner, Object* target = nullptr) const;
    ActionStatus heal(Object* owner, Object* target = nullptr) const;
    ActionStatus restore(Object* owner, Object* target = nullptr) const;

    bool checkAction(Actions action) const;
    bool hasProperty(Properties property) const;

    template <Properties param>
    friend decltype(auto) getOpt(is_object auto& object);

    template <Properties param>
    decltype(auto) getOpt() const;

    template <Properties param>
    decltype(auto) getOpt();
};

template <Properties param>
decltype(auto) getOpt(is_object auto& object) {
    if (object.hasProperty(param)) {
        return extract_optional_type<param>(object.object_->get(param));
    }
    using get_result_type = decltype(object.object_->get(param));
    return extract_optional_type<param>(get_result_type{});
}

template <Properties param>
decltype(auto) Object::getOpt() const {
    return ::getOpt<param>(*this);
}

template <Properties param>
decltype(auto) Object::getOpt() {
    return ::getOpt<param>(*this);
}

#include "ObjectModel.hpp"
