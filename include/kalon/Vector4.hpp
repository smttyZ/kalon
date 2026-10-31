#pragma once

#include <array>

#include <kalon/Real.hpp>

namespace kalon {

/**
 * @brief Stub for a 4D vector (homogeneous / spacetime).
 */
struct Vector4 {
private:
    std::array<Real, 4> _data{Real::Zero(), Real::Zero(), Real::Zero(), Real::Zero()};

public:
    Vector4() = default;
    Vector4(const Real& x, const Real& y, const Real& z, const Real& w) : _data{x, y, z, w} {}

    [[nodiscard]] Real X() const noexcept { return _data[0]; }
    [[nodiscard]] Real Y() const noexcept { return _data[1]; }
    [[nodiscard]] Real Z() const noexcept { return _data[2]; }
    [[nodiscard]] Real W() const noexcept { return _data[3]; }

    void SetX(const Real& x) noexcept { _data[0] = x; }
    void SetY(const Real& y) noexcept { _data[1] = y; }
    void SetZ(const Real& z) noexcept { _data[2] = z; }
    void SetW(const Real& w) noexcept { _data[3] = w; }

    /// @brief Direct element access (unchecked for now).
    [[nodiscard]] Real operator[](std::size_t idx) const noexcept { return _data[idx]; }
    Real& operator[](std::size_t idx) noexcept { return _data[idx]; }

    /// @brief TODO: add metric-aware operations (Minkowski vs Euclidean) once requirements are defined.
};

} // namespace kalon
