#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include "Enums/ActionStatus.hpp"
#include "Usage/Enums/Actions.hpp"
#include "Usage/Strategies.hpp"
#include "Taumaturgia/Traits/NameTraits.hpp"

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
    const std::unordered_map<Properties, const bool> has_;

public:
    template <Namingable T>
    Object(const T& obj)
        : object_{std::make_unique<ObjectModel<T>>(obj)},
          has_{propertiesExistanceMap<T>()} {}

    ActionStatus doAction(Actions action, Object* owner, Object* target) const;

    std::string name() const;
    std::optional<AliveStatus> alive() const;

    bool checkAction(Actions action) const;
    bool hasProperty(Properties property) const;

    template <Properties param>
    decltype(auto) getOpt(this auto& self) {
        if (self.hasProperty(param)) {
            return extract_optional_type<param>(self.object_->get(param));
        }
        using get_result_type = decltype(self.object_->get(param));
        return extract_optional_type<param>(get_result_type{});
    }
};

ActionStatus attack(const Object& object, Object* owner, Object* target = nullptr);
ActionStatus defend(const Object& object, Object* owner, Object* target = nullptr);
ActionStatus wear(const Object& object, Object* owner, Object* target = nullptr);
ActionStatus heal(const Object& object, Object* owner, Object* target = nullptr);
ActionStatus restore(const Object& object, Object* owner, Object* target = nullptr);

template <Properties param>
decltype(auto) getOpt(is_object auto& object) {
    return object.template getOpt<param>();
}

#include "ObjectModel.hpp"
