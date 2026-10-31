// Real.ipp
// kalon - Template definitions for Real (included at the end of Real.hpp)
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

    // Out-of-class definition of a member template: the template head is repeated without
    // its default argument, and `explicit` stays on the declaration in Real.hpp only.
    template <typename T, typename>
    constexpr Real::Real(T v) : _value(static_cast<double>(v)) {
        if (!isFinite(_value)) {
            throw std::domain_error("Real: value must be finite");
        }
    }

} // namespace kalon