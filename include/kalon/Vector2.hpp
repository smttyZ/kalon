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
    Real _x{Real::zero()};
    Real _y{Real::zero()};

public:
    Vector2() = default;
    Vector2(const Real& x, const Real& y) : _x(x), _y(y) {}

    [[nodiscard]] Real x() const noexcept { return _x; }
    [[nodiscard]] Real y() const noexcept { return _y; }

    void setX(const Real& x) noexcept { _x = x; }
    void setY(const Real& y) noexcept { _y = y; }
    void setComponents(const Real& x, const Real& y) noexcept {
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
