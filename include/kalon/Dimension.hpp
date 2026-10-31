#pragma once
#include "Real.hpp"
#include <cstdint>
#include <ratio>

/**
 * @file Dimension.hpp
 * @brief Compile-time physical dimensions (L, M, T) for dimensionally checked SI quantities.
 */

namespace kalon {

/**
 * @brief Shorthand for a rational exponent, e.g. Q<1>, Q<-2>, Q<1, 2>.
 * @tparam N Numerator of the exponent.
 * @tparam D Denominator of the exponent (defaults to 1 for integer powers).
 * @note Rational exponents allow fractional powers such as the square root of a length (Q<1, 2>).
 */
template <std::intmax_t N, std::intmax_t D = 1>
using Q = std::ratio<N, D>;

/**
 * @brief A scalar quantity tagged with its physical dimension at compile time.
 *
 * The dimension is encoded in the type as exponents of the base dimensions, so
 * quantities of different dimensions are distinct types. The stored value is
 * always expressed in SI base units (m, kg, s).
 *
 * @tparam L Exponent of length, as a std::ratio (see Q).
 * @tparam M Exponent of mass, as a std::ratio (see Q).
 * @tparam T Exponent of time, as a std::ratio (see Q).
 */
template <typename L, typename M, typename T>
class Dimension {
private:
    /// @brief Magnitude of the quantity in SI base units
    Real _value; // always SI

public:
    /**
     * @brief Construct a quantity from a value already in SI base units.
     * @param value Magnitude in SI units (e.g. metres for Length, seconds for Time).
     */
    constexpr explicit Dimension(Real value): _value(value) {}

    /**
     * @brief Accessor for the underlying magnitude.
     * @return The magnitude in SI base units.
     */
    [[nodiscard]] constexpr Real Value() const { return _value; }
};

/// @brief Length (L^1)
using Length       = Dimension<Q<1>, Q<0>, Q<0>>;
/// @brief Mass (M^1)
using Mass         = Dimension<Q<0>, Q<1>, Q<0>>;
/// @brief Time (T^1)
using Time         = Dimension<Q<0>, Q<0>, Q<1>>;
/// @brief Velocity (L^1 T^-1)
using Velocity     = Dimension<Q<1>, Q<0>, Q<-1>>;
/// @brief Acceleration (L^1 T^-2)
using Acceleration = Dimension<Q<1>, Q<0>, Q<-2>>;
/// @brief Force (L^1 M^1 T^-2)
using Force        = Dimension<Q<1>, Q<1>, Q<-2>>;

} // namespace kalon
