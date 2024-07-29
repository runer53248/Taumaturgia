#pragma once

#define StartCustomAccessMock(Name, Type)                                      \
    template <typename T>                                                      \
    struct traits::CustomAccessType<##Type, T> {                               \
        inline static traits::CustomAccessType<##Type, T>* mock = nullptr;     \
        static constexpr decltype(auto) get(auto& el) {                        \
            if (mock) {                                                        \
                return mock->get_(el);                                         \
            }                                                                  \
            throw std::logic_error("Mock not set for CustomAccess" #Name "!"); \
        }

#define EndCustomAccessMock() \
    }                         \
    ;

#define CustomMock(Name, Type) \
    template <typename T>      \
    using CustomAccess##Name##Mock = traits::CustomAccessType<##Type, T>;
