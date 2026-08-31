#pragma once

// MARK: empty

struct empty {
    empty() = default;
    empty(auto...) {}
};
