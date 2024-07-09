#pragma once
#include "Enums/ActionStatus.hpp"
#include "Usage/Strategies.hpp"

class Object;

class CommandConcept {
public:
    virtual ~CommandConcept() = default;
    virtual ActionStatus execute(Object* owner, Object* target) = 0;
};

template <template <typename> typename STRATEGY, typename T>
class CommandModel : public CommandConcept {
public:
    CommandModel(std::reference_wrapper<T> type)
        : type_{type} {}
    ~CommandModel() override = default;

    ActionStatus execute(Object* owner, Object* target) override {
        if constexpr (Strategable<STRATEGY, T, ActionStatus, Object*, Object*>) {
            return STRATEGY<T>::operator()(type_.get(), owner, target);
        } else {
            return ActionStatus::None;
        }
    }

private:
    std::reference_wrapper<T> type_;
};
