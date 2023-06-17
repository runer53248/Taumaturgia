#pragma once
#include <concepts>
#include <memory>
#include <optional>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

#include <experimental/propagate_const>
#include <functional>

class Object;

template <typename T>
concept Objected = std::same_as<T, Object> or std::same_as<T, const Object>;

class Object {
private:
    struct ObjectConcept {
        virtual ~ObjectConcept() = default;

        virtual std::string name() const = 0;
        virtual std::optional<bool> alive() const = 0;
        virtual bool attack(Object* owner, Object* targe) const = 0;
        virtual bool defend(Object* owner, Object* target) const = 0;
        virtual bool heal(Object* owner, Object* target) const = 0;
        virtual bool restore(Object* owner, Object* target) const = 0;
        virtual constexpr get_optional_variant_type get(Parameter param) = 0;
        virtual constexpr get_optional_variant_const_type get(Parameter param) const = 0;
    };

    template <Namingable T>
    struct ObjectModel : ObjectConcept {
    public:
        ObjectModel(const T& type)
            : type_{type} {}
        ~ObjectModel() override = default;

        std::string name() const override;
        std::optional<bool> alive() const override;
        bool attack(Object* owner, Object* target) const override;
        bool defend(Object* owner, Object* target) const override;
        bool heal(Object* owner, Object* target) const override;
        bool restore(Object* owner, Object* target) const override;
        constexpr get_optional_variant_type get(Parameter param) override;
        constexpr get_optional_variant_const_type get(Parameter param) const override;

    private:
        template <Parameter P>
        inline constexpr auto get_impl(Gettingable auto& type) const;
        inline constexpr auto get_impl(Gettingable auto& type, Parameter param) const;

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
          can_alive{AliveStrategable<AliveStrategy, T>},
          can_attack{AttackStrategable<AttackStrategy, T>},
          can_defend{DefendStrategable<DefendStrategy, T>},
          can_heal{HealStrategable<HealStrategy, T>},
          can_restore{RestoreStrategable<RestoreStrategy, T>},
          can_wear{WearStrategable<WearStrategy, T>},
          can_get{GetStrategable<GetStrategy, T>} {}

    std::string name() const;
    std::optional<bool> alive() const;
    bool attack(Object* owner, Object* target = nullptr) const;
    bool defend(Object* owner, Object* target = nullptr) const;
    bool heal(Object* owner, Object* target = nullptr) const;
    bool restore(Object* owner, Object* target = nullptr) const;

    template <Parameter param>
    bool checkGetParam() const;

    template <Parameter param>
    friend constexpr auto getOptVariant(Objected auto& object) -> decltype(object.object_->get(std::declval<Parameter>())) {  // return type depends on object constness
        if (not object.template checkGetParam<param>()) {
            return {};
        }
        return object.object_->get(param);
    }

    template <Parameter param>
    friend constexpr auto getOpt(Objected auto& object) {
        auto opt_variant = getOptVariant<param>(object);
        return get_opt_ref_wrapper<param>(opt_variant);
    }
};

#include "ObjectModel.hpp"
