#pragma once

#define StartCustomAccessMock(Name)                                            \
    template <typename T>                                                      \
    struct traits::CustomAccess##Name {                                        \
        inline static traits::CustomAccess##Name<T>* mock = nullptr;           \
        static constexpr decltype(auto) get(auto& el) {                                  \
            if (mock) {                                                        \
                return mock->get_(el);                                         \
            }                                                                  \
            throw std::logic_error("Mock not set for CustomAccess" #Name "!"); \
        }

#define EndCustomAccessMock() \
    }                         \
    ;

#define CustomMock(Name)  \
    template <typename T> \
    using CustomAccess##Name##Mock = traits::CustomAccess##Name<T>;
