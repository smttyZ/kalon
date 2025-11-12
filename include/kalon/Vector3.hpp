
#pragma once

/**
 * @file Vector3.hpp
 * @brief Defines the Vector3 class for 3D vector arithmetic with Real-based precision and SI unit tracking.
 * @todo(Henry): Extend to multiplicative/divisive unit composition for physical correctness (e.g., m/s * s = m).
 * @todo(Henry): Add proper file-level Doxygen banner and licensing notice per style guide.
 */

#include <cmath>
#include <string>
#include <string_view>

#include <kalon/Real.hpp>

namespace kalon {
    
struct Vector3 {
    // TODO(Henry): `_normalized` flag may become stale after scalar ops; consider resetting it in operator*= and operator/=.
    // TODO(Henry): Cross-product currently uses additive unit combination; should use multiplicative logic when available.
    // TODO(Henry): Add a ToString() or DebugString() helper for diagnostics and ASCII visualization.
    // TODO(Henry): Ensure Real is thread-safe before relying on mutable caches in concurrent contexts.
private:
    /// @brief The x, y, z components of the vector
    Real _x, _y, _z;

    /// @brief Cached flag for normalized vectors
    bool _normalized = false;

    /// @brief Mangnitude cache for expensive recalcs
    mutable Real _magnitudeCache = Real::zero();

    /// @brief Tracks whether the cached magnitude is valid
    mutable bool _magnitudeCacheValid = false;
    
    /// @brief SI unit tag (e.g., "m", "m/s")
    std::string _unit = "dimensionless";

    /// @brief Marker used when combining incompatible units
    static constexpr const char* kInconsistentUnits = "mixed units";

    /// @brief Combine units for additive operations, returns a stub if they differ
    [[nodiscard]] static std::string combineAdditiveUnits(const std::string& lhs, const std::string& rhs) {
        return lhs == rhs ? lhs : std::string(kInconsistentUnits);
    }

public:
    /// @brief Default constructor initializes the vector to (0, 0, 0)
    Vector3() : _x(Real::zero()), _y(Real::zero()), _z(Real::zero()) {}

    /// @brief Constructor that initializes the vector with given x, y, z components
    Vector3(const Real& x, const Real& y, const Real& z) : _x(x), _y(y), _z(z) {}

    /// @brief Accessor for x component
    [[nodiscard]] Real x() const noexcept {
        return _x;
    }

    /// @brief Accessor for y component
    [[nodiscard]] Real y() const noexcept {
        return _y;
    }

    /// @brief Accessor for z component
    [[nodiscard]] Real z() const noexcept {
        return _z;
    }

    /// @brief Mutator for x component
    void setX(const Real& x) noexcept {
        _x = x;
        InvalidateCache();
    }

    /// @brief Mutator for y component
    void setY(const Real& y) noexcept {
        _y = y;
        InvalidateCache();
    }

    /// @brief Mutator for z component
    void setZ(const Real& z) noexcept {
        _z = z;
        InvalidateCache();
    }

    /// @brief Set all vector components at once
    void setComponents(const Real& x, const Real& y, const Real& z) noexcept {
        _x = x;
        _y = y;
        _z = z;
        InvalidateCache();
    }

    // meta data accessors
    /// @brief Check if the vector is normalized
    /// @returns True if the vector is normalized, false otherwise
    [[nodiscard]] bool isNormalized() const noexcept {
        return _normalized;
    }

    /// @brief Get the unit of the vector
    /// @returns The SI unit tag as a string
    [[nodiscard]] const std::string& unit() const noexcept {
        return _unit;
    }

    /// @brief Set the unit of the vector (stores an owned copy)
    void setUnit(std::string_view unit) {
        _unit.assign(unit.begin(), unit.end());
    }

    /// @brief Invalidate the cached magnitude and normalized flag
    void InvalidateCache() noexcept {
        _magnitudeCache = Real::zero();
        _magnitudeCacheValid = false;
        _normalized = false;
    }

    /// @brief Calculate the magnitude of the vector
    /// @returns The magnitude as a Real number
    [[nodiscard]] Real Magnitude() const {
        if (!_magnitudeCacheValid) {
            Real magSquared = MagnitudeSquared();
            _magnitudeCache = Real(std::sqrt(magSquared.value()));
            _magnitudeCacheValid = true;
        }
        return _magnitudeCache;
    }

    /// @brief Compute the squared magnitude (avoids a square root)
    [[nodiscard]] Real MagnitudeSquared() const {
        return _x * _x + _y * _y + _z * _z;
    }

    /// @brief Return a normalized copy of the vector
    /// @returns A new Vector3 that is the normalized version of this vector
    [[nodiscard]] Vector3 Normalized() const {
        Real len = Magnitude();
        if (len == Real::zero()) return *this;
        Vector3 result(_x / len, _y / len, _z / len);
        result._normalized = true;
        result._unit = _unit;
        result._magnitudeCache = Real::one();
        result._magnitudeCacheValid = true;
        return result;
    }

    /// @brief Normalize the vector in-place if it has non-zero length
    void Normalize() {
        Real len = Magnitude();
        if (len == Real::zero()) {
            return;
        }
        _x = _x / len;
        _y = _y / len;
        _z = _z / len;
        _normalized = true;
        _magnitudeCache = Real::one();
        _magnitudeCacheValid = true;
    }

    /// @brief Compute the dot product with another vector
    [[nodiscard]] Real Dot(const Vector3& rhs) const {
        return _x * rhs._x + _y * rhs._y + _z * rhs._z;
    }

    /// @brief Compute the cross product with another vector
    [[nodiscard]] Vector3 Cross(const Vector3& rhs) const {
        Vector3 result(
            _y * rhs._z - _z * rhs._y,
            _z * rhs._x - _x * rhs._z,
            _x * rhs._y - _y * rhs._x
        );
        result._unit = combineAdditiveUnits(_unit, rhs._unit);
        return result;
    }

    /// @brief Negation operator
    [[nodiscard]] Vector3 operator-() const {
        Vector3 result(*this);
        result *= Real(-1.0);
        return result;
    }

    /// @brief Equality comparison (component-wise)
    [[nodiscard]] bool operator==(const Vector3& rhs) const noexcept {
        return _x == rhs._x && _y == rhs._y && _z == rhs._z && _unit == rhs._unit;
    }

    /// @brief Inequality comparison
    [[nodiscard]] bool operator!=(const Vector3& rhs) const noexcept {
        return !(*this == rhs);
    }

    /// @brief Add another vector to this one
    Vector3& operator+=(const Vector3& rhs) {
        _x = _x + rhs._x;
        _y = _y + rhs._y;
        _z = _z + rhs._z;
        _unit = combineAdditiveUnits(_unit, rhs._unit);
        InvalidateCache();
        return *this;
    }

    /// @brief Subtract another vector from this one
    Vector3& operator-=(const Vector3& rhs) {
        _x = _x - rhs._x;
        _y = _y - rhs._y;
        _z = _z - rhs._z;
        _unit = combineAdditiveUnits(_unit, rhs._unit);
        InvalidateCache();
        return *this;
    }

    /// @brief Scale the vector by a scalar
    Vector3& operator*=(const Real& scalar) {
        _x = _x * scalar;
        _y = _y * scalar;
        _z = _z * scalar;
        InvalidateCache();
        return *this;
    }

    /// @brief Divide the vector by a scalar
    Vector3& operator/=(const Real& scalar) {
        _x = _x / scalar;
        _y = _y / scalar;
        _z = _z / scalar;
        InvalidateCache();
        return *this;
    }

    /// @brief Vector addition
    [[nodiscard]] Vector3 operator+(const Vector3& rhs) const {
        Vector3 result(*this);
        result += rhs;
        return result;
    }

    /// @brief Vector subtraction
    [[nodiscard]] Vector3 operator-(const Vector3& rhs) const {
        Vector3 result(*this);
        result -= rhs;
        return result;
    }

    /// @brief Scalar multiplication
    [[nodiscard]] Vector3 operator*(const Real& scalar) const {
        Vector3 result(*this);
        result *= scalar;
        return result;
    }

    /// @brief Scalar division
    [[nodiscard]] Vector3 operator/(const Real& scalar) const {
        Vector3 result(*this);
        result /= scalar;
        return result;
    }

    /// @brief Scalar multiplication with the scalar on the left-hand side
    friend [[nodiscard]] Vector3 operator*(const Real& scalar, const Vector3& vec) {
        return vec * scalar;
    }



};
    
} // namespace kalon
