#pragma once
#include <string>

namespace Color {
inline constexpr std::string Red = "\033[1;31m";
inline constexpr std::string Green = "\033[1;32m";
inline constexpr std::string Yellow = "\033[1;33m";
inline constexpr std::string Blue = "\033[1;34m";
inline constexpr std::string White = "\033[1;37m";

inline constexpr std::string Reset = "\033[0m";
}  // namespace Color
