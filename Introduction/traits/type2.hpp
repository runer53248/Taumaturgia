#pragma once

struct Type2 {
    Name name_{"Type2"};

public:
    // decltype(auto) getName(this auto& self) { return (self.name_); }
    auto& getName() { return name_; }
    auto& getName() const { return name_; }
};
