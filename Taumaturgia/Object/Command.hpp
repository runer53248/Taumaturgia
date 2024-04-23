#pragma once
#include "Taumaturgia/Strategies/Strategies.hpp"

class CommandConcept {
public:
    virtual ~CommandConcept() = default;
    virtual ActionStatus execute(Object* owner, Object* target) = 0;
    virtual bool hasStrategy() const = 0;
};

template <typename T, template <typename> typename STRATEGY>
class CommandModel : public CommandConcept {
public:
    CommandModel(T& type)
        : type_{type} {}
    ~CommandModel() override = default;

    ActionStatus execute(Object* owner, Object* target) override {
        if constexpr (Strategable<STRATEGY, T>) {
            static constinit STRATEGY<T> strategy{};
            return strategy(type_, owner, target);
        }
        return ActionStatus::None;
    }

    bool hasStrategy() const override {
        return Strategable<STRATEGY, T>;
    }

private:
    T& type_;
};
