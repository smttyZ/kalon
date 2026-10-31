#pragma once
#include "Real.hpp"

/**
 * @file Dimension.hpp
 * @brief Compile-time physical dimensions (L, M, T).
 */

namespace kalon {

// TODO(Henry): exponent representation (int vs. std::ratio for fractional powers).
template <int L, int M, int T>
struct Dimension {
    Real _value; // always SI
};

    using Length            = Dimension<1, 0, 0>;
    using Mass              = Dimension<0, 1, 0>;
    using Time              = Dimension<0, 0, 1>;
    using Velocity          = Dimension<1, 0, -1>;
    using Acceleration      = Dimension<1, 0, -2>;
    using Force             = Dimension<1, 1, -2>;

}
