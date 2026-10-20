#pragma once

#include <kalon/Real.hpp>
#include <kalon/Vector3.hpp>
#include <kalon/Quaternion.hpp>

namespace kalon {

/**
 * @brief Position + orientation of a rigid body. Rotation is kept normalized.
 */
struct Transform {
private:
    Vector3 _position{};
    Quaternion _rotation{};

public:
    // position
    [[nodiscard]] Vector3 Position() const { return _position; }
    void SetPosition(const Vector3& p) { _position = p; }
    void Translate(const Vector3& delta) { _position += delta; }

    // rotation
    [[nodiscard]] Quaternion Rotation() const { return _rotation; }
    void SetRotation(const Quaternion& q) { _rotation = q.Normalized(); }
    /// @brief Apply `delta` on top of the current rotation (world frame).
    void Rotate(const Quaternion& delta) { _rotation = (delta * _rotation).Normalized(); }
};

} // namespace kalon
