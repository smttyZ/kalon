// Matrix3.hpp
// kalon - 3x3 matrix of Real
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

#include <array>

#include <kalon/Real.hpp>

namespace kalon {

/**
 * @brief 3x3 matrix stub suitable for rotations and inertia tensors.
 */
class Matrix3 {
public:
    using Storage = std::array<Real, 9>; // row-major

private:
    Storage _m{};

public:
    Matrix3() = default;

    explicit Matrix3(const Storage& values) : _m(values) {}

    /// @brief Access element at row r, column c.
    [[nodiscard]] Real operator()(std::size_t r, std::size_t c) const noexcept {
        return _m[r * 3 + c];
    }

    Real& operator()(std::size_t r, std::size_t c) noexcept {
        return _m[r * 3 + c];
    }

    /// @brief Reset to identity.
    void SetIdentity() noexcept {
        _m = Storage{Real::One(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::One(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::One()};
    }

    /// @brief TODO: determinants, inverses, basis transforms.
};

} // namespace kalon
