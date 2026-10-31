// Quaternion.hpp
// kalon - Rotation quaternion
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

#include <cmath>

#include <kalon/Real.hpp>
#include <kalon/Vector3.hpp>

namespace kalon {

/**
 * @brief Quaternion for orientation / rotation math, stored as (w, x, y, z).
 *
 * Default-constructs to the identity rotation (1, 0, 0, 0). Rotation helpers
 * assume a unit quaternion; call Normalized() first if unsure.
 */
class Quaternion {
private:
    Real _w{Real::One()};
    Real _x{Real::Zero()};
    Real _y{Real::Zero()};
    Real _z{Real::Zero()};

public:
    Quaternion() = default;
    Quaternion(const Real& w, const Real& x, const Real& y, const Real& z)
        : _w(w), _x(x), _y(y), _z(z) {}

    /// @brief The identity rotation.
    [[nodiscard]] static Quaternion Identity() noexcept { return Quaternion{}; }

    /// @brief Rotation of `angleRadians` about `axis` (axis is normalized internally).
    [[nodiscard]] static Quaternion FromAxisAngle(const Vector3& axis, const Real& angleRadians) {
        const Vector3 N = axis.Normalized();
        const double HALF = angleRadians.Value() * 0.5;
        const Real S(std::sin(HALF));
        return Quaternion(Real(std::cos(HALF)), N.X() * S, N.Y() * S, N.Z() * S);
    }

    [[nodiscard]] Real W() const noexcept { return _w; }
    [[nodiscard]] Real X() const noexcept { return _x; }
    [[nodiscard]] Real Y() const noexcept { return _y; }
    [[nodiscard]] Real Z() const noexcept { return _z; }

    void Set(const Real& w, const Real& x, const Real& y, const Real& z) noexcept {
        _w = w;
        _x = x;
        _y = y;
        _z = z;
    }

    /// @brief Squared norm (avoids a square root).
    [[nodiscard]] Real MagnitudeSquared() const {
        return _w * _w + _x * _x + _y * _y + _z * _z;
    }

    /// @brief Norm of the quaternion.
    [[nodiscard]] Real Magnitude() const {
        return Real(std::sqrt(MagnitudeSquared().Value()));
    }

    /// @brief Unit-length copy. A zero quaternion is returned unchanged,
    ///        matching Vector3::Normalized().
    [[nodiscard]] Quaternion Normalized() const {
        const Real LEN = Magnitude();
        if (LEN == Real::Zero())
            return *this;
        return Quaternion(_w / LEN, _x / LEN, _y / LEN, _z / LEN);
    }

    /// @brief Normalize in place (no-op for a zero quaternion).
    void Normalize() { *this = Normalized(); }

    /// @brief Conjugate (w, -x, -y, -z). Equals the inverse for unit quaternions.
    [[nodiscard]] Quaternion Conjugate() const {
        return Quaternion(_w, Real::Zero() - _x, Real::Zero() - _y, Real::Zero() - _z);
    }

    /// @brief Hamilton product. `a * b` applies rotation b first, then a.
    [[nodiscard]] Quaternion operator*(const Quaternion& rhs) const {
        return Quaternion(
            _w * rhs._w - _x * rhs._x - _y * rhs._y - _z * rhs._z,
            _w * rhs._x + _x * rhs._w + _y * rhs._z - _z * rhs._y,
            _w * rhs._y - _x * rhs._z + _y * rhs._w + _z * rhs._x,
            _w * rhs._z + _x * rhs._y - _y * rhs._x + _z * rhs._w
        );
    }

    /// @brief Rotate a vector by this (unit) quaternion: q * v * q^-1.
    ///        The vector's unit tag is preserved.
    [[nodiscard]] Vector3 Rotate(const Vector3& v) const {
        const Quaternion P(Real::Zero(), v.X(), v.Y(), v.Z());
        const Quaternion R = (*this) * P * Conjugate();
        Vector3 out(R._x, R._y, R._z);
        out.SetUnit(v.Unit());
        return out;
    }

    /// @brief Exact component-wise equality.
    [[nodiscard]] bool operator==(const Quaternion& rhs) const noexcept {
        return _w == rhs._w && _x == rhs._x && _y == rhs._y && _z == rhs._z;
    }
};

} // namespace kalon
