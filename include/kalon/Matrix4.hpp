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

    void setIdentity() noexcept {
        _m = Storage{
            Real::one(), Real::zero(), Real::zero(), Real::zero(),
            Real::zero(), Real::one(), Real::zero(), Real::zero(),
            Real::zero(), Real::zero(), Real::one(), Real::zero(),
            Real::zero(), Real::zero(), Real::zero(), Real::one()
        };
    }

    /// @brief TODO: implement multiplication, inversion, projection helpers.
};

} // namespace kalon
