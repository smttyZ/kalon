# kalon

A header-only C++20 math library for deterministic physics simulation. kalon is the math layer underneath the [Lambda Physics Engine](https://github.com/smttyZ/Lambda-Physics-Engine), which in turn powers [Project Lambda](https://github.com/smttyZ/Project-Lambda).

The central idea is that **invalid numbers can't exist**. kalon's scalar type, `Real`, refuses to hold `NaN` or `±inf`. Any operation that would produce one throws immediately, at the exact line that caused it, instead of letting a bad value spread silently through thousands of simulation steps.

```cpp
#include <kalon/Quaternion.hpp>
#include <numbers>

using namespace kalon;

Vector3 r(Real(1.0), Real(0.0), Real(0.0));
r.setUnit("m");

auto q = Quaternion::FromAxisAngle(Vector3(Real(0.0), Real(0.0), Real(1.0)),
                                   Real(std::numbers::pi / 2));
Vector3 rotated = q.Rotate(r);   // (0, 1, 0), still tagged "m"

Real bad = Real(1.0) / Real(0.0); // throws std::domain_error
```

## Status

| Type | State |
|---|---|
| `Real` | ✅ Finite-checked `double` wrapper: arithmetic, comparisons, epsilon |
| `Vector3` | ✅ Arithmetic, dot/cross, cached magnitude, normalize, per-vector unit tags |
| `Quaternion` | ✅ Axis-angle construction, normalize, conjugate, Hamilton product, vector rotation |
| `Transform` | ✅ Position + always-normalized rotation |
| `Vector2`, `Vector4` | 🚧 Storage and accessors only |
| `Matrix3`, `Matrix4` | 🚧 Storage, element access, identity only |
| `Constants` | 🚧 Placeholder values (c, G, h) |

## Building and testing

Requires CMake ≥ 3.23 and a C++20 compiler. Tested with GCC 13 and Clang 18. The tests also need [GoogleTest](https://github.com/google/googletest) (`libgtest-dev` on Ubuntu, `brew install googletest` on macOS).

```sh
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or in a container:

```sh
docker build -t kalon .
docker run --rm kalon
```

## Using kalon in your project

**As a subdirectory or git submodule** (this is how the Lambda Physics Engine consumes it). Tests are off by default when kalon isn't the top-level project, so you don't need GoogleTest:

```cmake
add_subdirectory(external/kalon)
target_link_libraries(your_target PRIVATE kalon::kalon)
```

**As an installed package:**

```sh
cmake -B build -DKALON_BUILD_TESTS=OFF
cmake --install build --prefix /your/prefix
```

```cmake
find_package(kalon REQUIRED)
target_link_libraries(your_target PRIVATE kalon::kalon)
```

## Design notes

- **`Real` throws on non-finite results.** This trades raw speed for catching numerical bugs at their source. For research simulations, a wrong answer that looks plausible is worse than a crash.
- **Units are tracked per vector.** Adding two `Vector3`s with different unit tags produces the tag `"mixed units"` rather than silently picking one. Units are currently runtime strings, and only additive combination is implemented.

### Open design questions

- **Compile-time units.** Moving unit tracking into the type system (so `meters + seconds` fails to compile) would make the library strongly typed in the full sense and remove the per-vector string allocation.
- **An exception-free path.** GPU kernels can't throw. Supporting GPU workloads will need a variant of `Real` that reports errors another way (status flags, checked/unchecked modes, or similar).

## License

Apache License 2.0. See [LICENSE](LICENSE).
