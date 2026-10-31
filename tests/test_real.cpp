#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <stdexcept>

#include <kalon/Real.hpp>

using kalon::Real;

// Real must stay usable in constant expressions (needs C++23 constexpr <cmath>).
static_assert((Real(2.0) * Real(3.0)).Value() == 6.0);

TEST(Real, DefaultsToZero) {
    EXPECT_EQ(Real{}.Value(), 0.0);
    EXPECT_EQ(Real::Zero().Value(), 0.0);
    EXPECT_EQ(Real::One().Value(), 1.0);
}

TEST(Real, ConstructsFromArithmeticTypes) {
    EXPECT_EQ(Real(3).Value(), 3.0);
    EXPECT_EQ(Real(2.5f).Value(), 2.5);
    EXPECT_EQ(Real(7L).Value(), 7.0);
}

TEST(Real, Arithmetic) {
    EXPECT_EQ((Real(2.0) + Real(3.0)).Value(), 5.0);
    EXPECT_EQ((Real(2.0) - Real(3.0)).Value(), -1.0);
    EXPECT_EQ((Real(2.0) * Real(3.0)).Value(), 6.0);
    EXPECT_EQ((Real(6.0) / Real(3.0)).Value(), 2.0);
}

TEST(Real, Comparisons) {
    EXPECT_TRUE(Real(1.0) < Real(2.0));
    EXPECT_TRUE(Real(2.0) > Real(1.0));
    EXPECT_TRUE(Real(1.0) <= Real(1.0));
    EXPECT_TRUE(Real(1.0) >= Real(1.0));
    EXPECT_TRUE(Real(1.0) == Real(1.0));
    EXPECT_TRUE(Real(1.0) != Real(2.0));
}

// The core guarantee: non-finite values can never exist inside a Real.
TEST(Real, RejectsNonFiniteConstruction) {
    EXPECT_THROW(static_cast<void>(Real(std::numeric_limits<double>::quiet_NaN())), std::domain_error);
    EXPECT_THROW(static_cast<void>(Real(std::numeric_limits<double>::infinity())), std::domain_error);
    EXPECT_THROW(static_cast<void>(Real(-std::numeric_limits<double>::infinity())), std::domain_error);
}

TEST(Real, ThrowsOnDivisionByZero) {
    EXPECT_THROW(static_cast<void>(Real(1.0) / Real::Zero()), std::domain_error);
}

TEST(Real, ThrowsOnOverflow) {
    const Real huge(std::numeric_limits<double>::max());
    EXPECT_THROW(static_cast<void>(huge * Real(10.0)), std::domain_error);
    EXPECT_THROW(static_cast<void>(huge + huge), std::domain_error);
    EXPECT_THROW(static_cast<void>(Real::Zero() - huge - huge), std::domain_error);
}

TEST(Real, EpsilonMatchesDouble) {
    EXPECT_EQ(Real::Epsilon().Value(), std::numeric_limits<double>::epsilon());
}
