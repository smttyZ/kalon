// Constants.hpp
// kalon - Physical constants (placeholder values)
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <kalon/Real.hpp>

namespace kalon::constants {

/// @brief Placeholder physical constants (to be calibrated for research scenarios).
inline constexpr Real SpeedOfLight() noexcept { return Real(299'792'458.0); }
inline constexpr Real GravitationalConstant() noexcept { return Real(6.67430e-11); }
inline constexpr Real PlanckConstant() noexcept { return Real(6.62607015e-34); }

/// @brief TODO: add domain-specific constants (solar mass, electron charge, etc.).

} // namespace kalon::constants
