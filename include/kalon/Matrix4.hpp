// Matrix4.hpp
// kalon - 4x4 matrix of Real
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
 * @brief 4x4 matrix stub for affine/relativistic transforms.
 */
class Matrix4 {
public:
    using Storage = std::array<Real, 16>; // row-major

private:
    Storage _m{};

public:
    Matrix4() = default;

    explicit Matrix4(const Storage& values) : _m(values) {}

    [[nodiscard]] Real operator()(std::size_t r, std::size_t c) const noexcept {
        return _m[r * 4 + c];
    }

    Real& operator()(std::size_t r, std::size_t c) noexcept {
        return _m[r * 4 + c];
    }

    void SetIdentity() noexcept {
        _m = Storage{Real::One(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::One(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::One(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::Zero(),
                     Real::One()};
    }

    /// @brief TODO: implement multiplication, inversion, projection helpers.
};

} // namespace kalon
