#pragma once

#include <type_traits>
#include <stdexcept>
#include <cmath>
#include <limits>

namespace kalon {

class Real final {
private:
    double _value;
    
    // Internal finite check helper
    static constexpr bool isFinite(double v) noexcept {
        return std::isfinite(v);
    }

public:

    /**
     * Default constructor initializes the Real number to zero.
     */
    constexpr Real() : _value(0.0) {}

    /**
     * Constructor that initializes the Real number from any arithmetic type.
     */
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    constexpr explicit Real(T v) : _value(static_cast<double>(v)) {
        if (!isFinite(_value)) {
            throw std::domain_error("Real: value must be finite");
        }
    }

    /// @brief Accessor
    [[nodiscard]] constexpr double value() const {
        return _value;
    }

    // operators
        [[nodiscard]] constexpr Real operator+(const Real& rhs) const {
        double result = _value + rhs._value;
        if (!isFinite(result)) throw std::domain_error("Real addition produced non-finite result");
        return Real(result);
    }

    [[nodiscard]] constexpr Real operator-(const Real& rhs) const {
        double result = _value - rhs._value;
        if (!isFinite(result)) throw std::domain_error("Real subtraction produced non-finite result");
        return Real(result);
    }

    [[nodiscard]] constexpr Real operator*(const Real& rhs) const {
        double result = _value * rhs._value;
        if (!isFinite(result)) throw std::domain_error("Real multiplication produced non-finite result");
        return Real(result);
    }

    [[nodiscard]] constexpr Real operator/(const Real& rhs) const {
        if (rhs._value == 0.0) throw std::domain_error("Real: division by zero");
        double result = _value / rhs._value;
        if (!isFinite(result)) throw std::domain_error("Real division produced non-finite result");
        return Real(result);
    }

    // comparisons
    [[nodiscard]] constexpr bool operator==(const Real& rhs) const noexcept {
        return _value == rhs._value;
    }
    [[nodiscard]] constexpr bool operator!=(const Real& rhs) const noexcept {
        return !(*this == rhs);
    }
    [[nodiscard]] constexpr bool operator<(const Real& rhs) const noexcept {
        return _value < rhs._value;
    }
    [[nodiscard]] constexpr bool operator>(const Real& rhs) const noexcept {
        return _value > rhs._value;
    }
    [[nodiscard]] constexpr bool operator<=(const Real& rhs) const noexcept {
        return _value <= rhs._value;
    }
    [[nodiscard]] constexpr bool operator>=(const Real& rhs) const noexcept {
        return _value >= rhs._value;
    }

    // util
    static constexpr Real epsilon() noexcept {
        return Real(std::numeric_limits<double>::epsilon());
    }

    static constexpr Real zero() noexcept { return Real(0.0); }
    static constexpr Real one() noexcept { return Real(1.0); }



};

}