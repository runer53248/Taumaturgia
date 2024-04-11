#pragma once
#include <iostream>
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"

constexpr const char* toString(ActionStatus status) noexcept {
    switch (status) {
    case ActionStatus::None:
        return "None";
    case ActionStatus::Invalid:
        return "Invalid";
    case ActionStatus::Fail:
        return "Fail";
    case ActionStatus::Interrupted:
        return "Interrupted";
    case ActionStatus::Partial_Success:
        return "Partial_Success";
    case ActionStatus::Success:
        return "Success";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, ActionStatus actionStatus) {
    return out << ' ' << toString(actionStatus) << ' ';
}
