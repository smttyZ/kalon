// Vector2.hpp
// kalon - 2D vector of Real
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

namespace kalon {

/**
 * @brief Lightweight 2D vector stub.
 * 
 * This type mirrors the structure of Vector3 but keeps the implementation
 * intentionally minimal so additional operations can be layered on later.
 */
struct Vector2 {
private:
    Real _x{Real::Zero()};
    Real _y{Real::Zero()};

public:
    Vector2() = default;
    Vector2(const Real& x, const Real& y) : _x(x), _y(y) {}

    [[nodiscard]] Real X() const noexcept { return _x; }
    [[nodiscard]] Real Y() const noexcept { return _y; }

    void SetX(const Real& x) noexcept { _x = x; }
    void SetY(const Real& y) noexcept { _y = y; }
    void SetComponents(const Real& x, const Real& y) noexcept {
        _x = x;
        _y = y;
    }

    /// @brief Placeholder magnitude helper (no caching here yet).
    [[nodiscard]] Real MagnitudeSquared() const {
        return _x * _x + _y * _y;
    }

    /// @brief TODO: add normalization/ops to match Vector3 once requirements stabilize.
};

} // namespace kalon
