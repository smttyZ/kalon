// Real.hpp
// kalon - Finite-checked double-precision scalar
// Copyright (C) 2025
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>

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
        constexpr explicit Real(T v); // defined in Real.ipp

        /// @brief Accessor
        [[nodiscard]] constexpr double Value() const {
            return _value;
        }

        // operators
        [[nodiscard]] constexpr Real operator+(const Real& rhs) const {
            double result = _value + rhs._value;
            if (!isFinite(result))
                throw std::domain_error("Real addition produced non-finite result");
            return Real(result);
        }

        [[nodiscard]] constexpr Real operator-(const Real& rhs) const {
            double result = _value - rhs._value;
            if (!isFinite(result))
                throw std::domain_error("Real subtraction produced non-finite result");
            return Real(result);
        }

        [[nodiscard]] constexpr Real operator*(const Real& rhs) const {
            double result = _value * rhs._value;
            if (!isFinite(result))
                throw std::domain_error("Real multiplication produced non-finite result");
            return Real(result);
        }

        [[nodiscard]] constexpr Real operator/(const Real& rhs) const {
            if (rhs._value == 0.0)
                throw std::domain_error("Real: division by zero");
            double result = _value / rhs._value;
            if (!isFinite(result))
                throw std::domain_error("Real division produced non-finite result");
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
        static constexpr Real Epsilon() noexcept {
            return Real(std::numeric_limits<double>::epsilon());
        }

        static constexpr Real Zero() noexcept {
            return Real(0.0);
        }
        static constexpr Real One() noexcept {
            return Real(1.0);
        }
    };

} // namespace kalon

// Template definitions (STYLEGUIDE.md section 2).
#include "Real.ipp"