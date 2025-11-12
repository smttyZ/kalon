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
    void setIdentity() noexcept {
        _m = Storage{
            Real::one(), Real::zero(), Real::zero(),
            Real::zero(), Real::one(), Real::zero(),
            Real::zero(), Real::zero(), Real::one()
        };
    }

    /// @brief TODO: determinants, inverses, basis transforms.
};

} // namespace kalon
