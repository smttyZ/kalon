#pragma once

#include <kalon/Real.hpp>

namespace kalon {

/**
 * @brief Quaternion stub for orientation / rotation math.
 */
class Quaternion {
private:
    Real _w{Real::one()};
    Real _x{Real::zero()};
    Real _y{Real::zero()};
    Real _z{Real::zero()};

public:
    Quaternion() = default;
    Quaternion(const Real& w, const Real& x, const Real& y, const Real& z)
        : _w(w), _x(x), _y(y), _z(z) {}

    [[nodiscard]] Real w() const noexcept { return _w; }
    [[nodiscard]] Real x() const noexcept { return _x; }
    [[nodiscard]] Real y() const noexcept { return _y; }
    [[nodiscard]] Real z() const noexcept { return _z; }

    void set(const Real& w, const Real& x, const Real& y, const Real& z) noexcept {
        _w = w;
        _x = x;
        _y = y;
        _z = z;
    }

    /// @brief TODO: add normalization, multiplication, conversion to/from matrices when equations are finalized.
};

} // namespace kalon
