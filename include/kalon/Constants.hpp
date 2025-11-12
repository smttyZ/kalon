#pragma once

#include <kalon/Real.hpp>

namespace kalon::constants {

/// @brief Placeholder physical constants (to be calibrated for research scenarios).
inline constexpr Real SpeedOfLight() noexcept { return Real(299'792'458.0); }
inline constexpr Real GravitationalConstant() noexcept { return Real(6.67430e-11); }
inline constexpr Real PlanckConstant() noexcept { return Real(6.62607015e-34); }

/// @brief TODO: add domain-specific constants (solar mass, electron charge, etc.).

} // namespace kalon::constants
