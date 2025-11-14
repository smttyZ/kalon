#pragma once
#include <kalon/Real.hpp>
#include <kalon/Vector3.hpp>
#include <kalon/Quaternion.hpp>

using kalon::Vector3;
using kalon::Quaternion;

namespace kalon {
    struct Transform {
    private:
        Vector3 _position{};
        Quaternion _rotation{};


    public:

        // public position
        [[nodiscard]] Vector3 Position() { return _position; }
        void SetPosition(const Vector3& p) noexcept { _position = p; }
        void Translate(const Vector3& delta) noexcept { _position += delta; }

        // public rotation
        [[nodiscard]] Quaternion Rotation() { return _rotation; }
        void SetRotation(const Quaternion& q) noexcept { _rotation = q.Normalized; }
        void Rotate(const Quaternion& delta) noexcept { _rotation = (delta * _rotation).Normalized(); }
    };
}