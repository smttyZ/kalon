#include <gtest/gtest.h>

#include <numbers>

#include <kalon/Quaternion.hpp>
#include <kalon/Transform.hpp>

using kalon::Quaternion;
using kalon::Real;
using kalon::Transform;
using kalon::Vector3;

namespace {
constexpr double kPi = std::numbers::pi;

Vector3 v(double x, double y, double z) { return Vector3(Real(x), Real(y), Real(z)); }

void ExpectNear(const Vector3& a, double x, double y, double z, double tol = 1e-12) {
    EXPECT_NEAR(a.x().value(), x, tol);
    EXPECT_NEAR(a.y().value(), y, tol);
    EXPECT_NEAR(a.z().value(), z, tol);
}
} // namespace

TEST(Quaternion, DefaultIsIdentity) {
    const Quaternion q;
    EXPECT_EQ(q, Quaternion::Identity());
    EXPECT_EQ(q.w().value(), 1.0);
    ExpectNear(q.Rotate(v(1, 2, 3)), 1, 2, 3);
}

TEST(Quaternion, NormalizeAndMagnitude) {
    const Quaternion q(Real(1.0), Real(1.0), Real(1.0), Real(1.0));
    EXPECT_EQ(q.Magnitude().value(), 2.0);
    EXPECT_NEAR(q.Normalized().Magnitude().value(), 1.0, 1e-15);

    const Quaternion zero(Real(0.0), Real(0.0), Real(0.0), Real(0.0));
    EXPECT_EQ(zero.Normalized(), zero); // mirrors Vector3: zero stays zero
}

TEST(Quaternion, AxisAngleRotatesVectors) {
    const Quaternion z90 = Quaternion::FromAxisAngle(v(0, 0, 1), Real(kPi / 2));
    ExpectNear(z90.Rotate(v(1, 0, 0)), 0, 1, 0);
    ExpectNear(z90.Rotate(v(0, 1, 0)), -1, 0, 0);
    ExpectNear(z90.Rotate(v(0, 0, 1)), 0, 0, 1); // axis is invariant

    // Axis need not be unit length.
    const Quaternion x180 = Quaternion::FromAxisAngle(v(5, 0, 0), Real(kPi));
    ExpectNear(x180.Rotate(v(0, 1, 0)), 0, -1, 0);
}

TEST(Quaternion, ProductComposesRotations) {
    const Quaternion z90 = Quaternion::FromAxisAngle(v(0, 0, 1), Real(kPi / 2));
    ExpectNear((z90 * z90).Rotate(v(1, 0, 0)), -1, 0, 0);

    // a * b applies b first: rotate about x, then about z.
    const Quaternion x90 = Quaternion::FromAxisAngle(v(1, 0, 0), Real(kPi / 2));
    ExpectNear((z90 * x90).Rotate(v(0, 1, 0)), 0, 0, 1);  // y -x-> z, z -z-> z
    ExpectNear((x90 * z90).Rotate(v(0, 1, 0)), -1, 0, 0); // y -z-> -x, -x -x-> -x
}

TEST(Quaternion, ConjugateUndoesRotation) {
    const Quaternion q = Quaternion::FromAxisAngle(v(1, 2, 3), Real(0.7));
    const Vector3 p = v(4, -5, 6);
    const Vector3 back = q.Conjugate().Rotate(q.Rotate(p));
    ExpectNear(back, 4, -5, 6, 1e-12);
}

TEST(Quaternion, RotatePreservesUnitTagAndLength) {
    Vector3 p = v(3, 4, 0);
    p.setUnit("m");
    const Vector3 r = Quaternion::FromAxisAngle(v(0, 1, 0), Real(1.234)).Rotate(p);
    EXPECT_EQ(r.unit(), "m");
    EXPECT_NEAR(r.Magnitude().value(), 5.0, 1e-12);
}

TEST(Transform, TranslateAndKeepRotationNormalized) {
    Transform t;
    t.SetPosition(v(1, 1, 1));
    t.Translate(v(1, 2, 3));
    ExpectNear(t.Position(), 2, 3, 4);

    // Non-unit input is normalized on the way in.
    t.SetRotation(Quaternion(Real(2.0), Real(0.0), Real(0.0), Real(0.0)));
    EXPECT_EQ(t.Rotation(), Quaternion::Identity());

    const Quaternion z90 = Quaternion::FromAxisAngle(v(0, 0, 1), Real(kPi / 2));
    t.Rotate(z90);
    t.Rotate(z90);
    EXPECT_NEAR(t.Rotation().Magnitude().value(), 1.0, 1e-15);
    ExpectNear(t.Rotation().Rotate(v(1, 0, 0)), -1, 0, 0);
}
