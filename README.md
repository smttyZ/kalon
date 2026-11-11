# kalon

A header-only C++23 math library for deterministic physics simulation. kalon is the math layer underneath the [Lambda Physics Engine](https://github.com/smttyZ/Lambda-Physics-Engine), which in turn powers [Project Lambda](https://github.com/smttyZ/Project-Lambda).

The central idea is that **invalid numbers can't exist**. kalon's scalar type, `Real`, refuses to hold `NaN` or `±inf`. Any operation that would produce one throws immediately, at the exact line that caused it, instead of letting a bad value spread silently through thousands of simulation steps.

```cpp
#include <kalon/Quaternion.hpp>
#include <numbers>

using namespace kalon;

Vector3 r(Real(1.0), Real(0.0), Real(0.0));
r.SetUnit("m");

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

Requires CMake ≥ 3.23 and a C++23 compiler. Tested with Apple Clang 21 on macOS. The tests also need [GoogleTest](https://github.com/google/googletest) (`libgtest-dev` on Ubuntu, `brew install googletest` on macOS).

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

## What "strongly typed" means here

In kalon, strongly typed means that **values that share a representation but mean different things get different types**, so mixing them up is a *compile* error rather than a runtime surprise. Meters and seconds are both stored as `double`, but `meters + seconds` should not compile.

`Real` already works this way relative to `double`:

```cpp
Real a = 5.0;          // ✗ does not compile: no implicit double -> Real
Real b(5.0);           // ✓ explicit construction
double d = b;          // ✗ does not compile: no implicit Real -> double
double e = b.Value();  // ✓ explicit
```

Units are not there yet. Today they are runtime string tags, so `meters + seconds` compiles and produces a vector tagged `"mixed units"` that you have to check for yourself. A typo (`"meter"` vs `"m"`) looks the same as a genuine mismatch.

## Goals vs. today

| Goal | Today | What's needed |
|---|---|---|
| **Strongly typed units:** dimension mismatches fail to compile | Runtime string tags; only additive combination; one string allocation per vector | Encode dimensions in the type system (compile-time units) |
| **GPU workloads** | CPU only; every `Real` operation can throw, and GPU kernels can't throw | An error-reporting path that doesn't use exceptions |
| **Fail loudly on bad math** | ✅ `Real` rejects NaN/±inf at construction and after every operation | — |

### Known limitations

- `Real`'s constructor accepts any arithmetic type, and C++ counts `bool` as arithmetic, so `Real(true)` compiles and equals `1.0`.
- `Real` operations throw, which makes almost nothing in kalon `noexcept`.

## Design notes

- **`Real` throws on non-finite results.** This trades raw speed for catching numerical bugs at their source. For research simulations, a wrong answer that looks plausible is worse than a crash.
- **Unit tags combine conservatively.** Adding two `Vector3`s with different tags produces `"mixed units"` rather than silently picking one.

## License

Apache License 2.0. See [LICENSE](LICENSE).
