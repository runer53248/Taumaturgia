#pragma once
#include <string>

namespace Color {
inline constexpr std::string Red = "\033[1;31m";
inline constexpr std::string Green = "\033[1;32m";
inline constexpr std::string Yellow = "\033[1;33m";
inline constexpr std::string Blue = "\033[1;34m";
inline constexpr std::string White = "\033[1;37m";
inline constexpr std::string Grey = "\033[1;90m";

inline constexpr std::string RedBack = "\033[1;41m";
inline constexpr std::string GreenBack = "\033[1;42m";
inline constexpr std::string YellowBack = "\033[1;43m";
inline constexpr std::string BlueBack = "\033[1;44m";
inline constexpr std::string GreyBack = "\033[1;100m";

inline constexpr std::string Reset = "\033[0m";
}  // namespace Color
