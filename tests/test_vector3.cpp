#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

#include <kalon/Vector3.hpp>

using kalon::Real;
using kalon::Vector3;

namespace {
Vector3 v(double x, double y, double z) { return Vector3(Real(x), Real(y), Real(z)); }

void ExpectNear(const Vector3& a, double x, double y, double z, double tol = 1e-12) {
    EXPECT_NEAR(a.x().value(), x, tol);
    EXPECT_NEAR(a.y().value(), y, tol);
    EXPECT_NEAR(a.z().value(), z, tol);
}
} // namespace

TEST(Vector3, DefaultsToZeroAndDimensionless) {
    const Vector3 z;
    ExpectNear(z, 0, 0, 0);
    EXPECT_EQ(z.unit(), "dimensionless");
    EXPECT_FALSE(z.isNormalized());
}

TEST(Vector3, AddSubtractScale) {
    ExpectNear(v(1, 2, 3) + v(4, 5, 6), 5, 7, 9);
    ExpectNear(v(4, 5, 6) - v(1, 2, 3), 3, 3, 3);
    ExpectNear(v(1, 2, 3) * Real(2.0), 2, 4, 6);
    ExpectNear(Real(2.0) * v(1, 2, 3), 2, 4, 6);
    ExpectNear(v(2, 4, 6) / Real(2.0), 1, 2, 3);
    ExpectNear(-v(1, -2, 3), -1, 2, -3);
}

TEST(Vector3, DotAndCross) {
    EXPECT_EQ(v(1, 2, 3).Dot(v(4, 5, 6)).value(), 32.0);
    ExpectNear(v(1, 0, 0).Cross(v(0, 1, 0)), 0, 0, 1);  // x × y = z
    ExpectNear(v(0, 1, 0).Cross(v(1, 0, 0)), 0, 0, -1); // anti-commutative
}

TEST(Vector3, MagnitudeAndCache) {
    Vector3 a = v(3, 4, 0);
    EXPECT_EQ(a.MagnitudeSquared().value(), 25.0);
    EXPECT_EQ(a.Magnitude().value(), 5.0);
    a.setX(Real(0.0)); // mutation must invalidate the cached magnitude
    EXPECT_EQ(a.Magnitude().value(), 4.0);
}

TEST(Vector3, NormalizeTracksFlag) {
    const Vector3 n = v(3, 4, 0).Normalized();
    ExpectNear(n, 0.6, 0.8, 0.0);
    EXPECT_TRUE(n.isNormalized());
    EXPECT_EQ(n.Magnitude().value(), 1.0);

    Vector3 m = v(0, 0, 2);
    m.Normalize();
    ExpectNear(m, 0, 0, 1);
    EXPECT_TRUE(m.isNormalized());

    m *= Real(3.0); // scaling must clear the normalized flag
    EXPECT_FALSE(m.isNormalized());
}

TEST(Vector3, NormalizingZeroIsANoOp) {
    const Vector3 z;
    ExpectNear(z.Normalized(), 0, 0, 0);
    EXPECT_FALSE(z.Normalized().isNormalized());
}

TEST(Vector3, UnitTagsCombineAdditively) {
    Vector3 a = v(1, 0, 0);
    Vector3 b = v(0, 1, 0);
    a.setUnit("m");
    b.setUnit("m");
    EXPECT_EQ((a + b).unit(), "m");

    b.setUnit("s");
    EXPECT_EQ((a + b).unit(), "mixed units");
}

TEST(Vector3, EqualityIncludesUnit) {
    Vector3 a = v(1, 2, 3);
    Vector3 b = v(1, 2, 3);
    EXPECT_EQ(a, b);
    b.setUnit("m");
    EXPECT_NE(a, b);
}

TEST(Vector3, DivideByZeroThrows) {
    EXPECT_THROW(static_cast<void>(v(1, 2, 3) / Real::zero()), std::domain_error);
}
