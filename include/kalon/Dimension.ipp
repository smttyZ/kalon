// Dimension.ipp
// kalon - Template definitions for Dimensions
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

namespace kalon {

    template <typename L, typename M, typename T>
    constexpr Dimension<L, M, T> Dimension<L, M, T>::operator+(const Dimension<L, M, T>& rhs) const
    {
        return Dimension(_value + rhs._value);
    }

    template <typename L, typename M, typename T>
    constexpr Dimension<L, M, T> Dimension<L, M, T>::operator-(const Dimension<L, M, T>& rhs) const
    {
        return Dimension(_value - rhs._value);
    }
}
