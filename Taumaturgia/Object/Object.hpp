#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include "Taumaturgia/Concepts/Namingable.hpp"
#include "Taumaturgia/Enums/Actions.hpp"
#include "Taumaturgia/Strategies/Strategies.hpp"

#ifndef _MSC_VER
#include <experimental/propagate_const>
#endif

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
        virtual constexpr get_optional_variant_type get(Parameter param) = 0;
        virtual constexpr get_optional_variant_const_type get(Parameter param) const = 0;
    };

    template <Namingable T>
    class ObjectModel : public ObjectConcept {
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

#ifndef _MSC_VER
    std::experimental::propagate_const<std::unique_ptr<ObjectConcept>> object_;
#else
    std::unique_ptr<ObjectConcept> object_;
#endif

    ActionStatus doAction(Actions action, Object* owner, Object* target) const;

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

    bool checkAction(Actions action) const;
    bool checkGetParam(Parameter param) const;

    template <Parameter param>
    friend decltype(auto) getOpt(is_object auto& object);

    template <Parameter param>
    decltype(auto) getOpt() const;

    template <Parameter param>
    decltype(auto) getOpt();
};

template <Parameter param>
decltype(auto) getOpt(is_object auto& object) {
    if (object.checkGetParam(param)) {
        return get_opt_ref_wrapper<param>(object.object_->get(param));
    }
    using get_result_type = decltype(object.object_->get(param));
    return get_opt_ref_wrapper<param>(get_result_type{});
}

template <Parameter param>
decltype(auto) Object::getOpt() const {
    return ::getOpt<param>(*this);
}

template <Parameter param>
decltype(auto) Object::getOpt() {
    return ::getOpt<param>(*this);
}

#include "ObjectModel.hpp"
