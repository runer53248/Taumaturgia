#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#ifndef _MSC_VER
#include <experimental/propagate_const>
#endif
#include "Command.hpp"

enum class Actions;

template <typename T>
concept is_object = std::same_as<T, Object> or std::same_as<T, const Object>;

class Object {
private:
    class ObjectConcept {  // TODO: implement copy
    public:
        virtual constexpr ~ObjectConcept() = default;

        virtual constexpr auto name() const -> std::string = 0;
        virtual constexpr auto alive() const -> std::optional<AliveStatus> = 0;
        virtual constexpr auto action(Actions action, Object* owner, Object* target) const -> ActionStatus = 0;
        virtual constexpr auto get(Properties param) -> optional_get_variant_type = 0;
        virtual constexpr auto get(Properties param) const -> optional_get_variant_const_type = 0;
    };

    template <Namingable T>
    class ObjectModel : public ObjectConcept {
    public:
        constexpr ObjectModel(const T& type);
        constexpr ~ObjectModel() override = default;

        constexpr auto name() const -> std::string override;
        constexpr auto alive() const -> std::optional<AliveStatus> override;
        constexpr auto action(Actions action, Object* owner, Object* target) const -> ActionStatus override;
        constexpr auto get(Properties param) -> optional_get_variant_type override;
        constexpr auto get(Properties param) const -> optional_get_variant_const_type override;

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

    template <Properties param, typename Self>
    decltype(auto) getOpt(this Self& self) {
        if (self.hasProperty(param)) {
            return extract_optional_type<param>(self.object_->get(param));
        }
        return get_result_type<param, std::is_const_v<Self>>{};
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
