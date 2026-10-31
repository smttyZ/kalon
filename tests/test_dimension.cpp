// tests/test_dimension.cpp
//
// Compile-time tests for kalon/Dimension.hpp. The real checks are static_asserts, so a
// failure shows up as a BUILD error, not a failing test. The TEST() blocks only give
// ctest something to report.
//
// How to use: every STEP block below is commented out. When you finish that step in
// Dimension.hpp, uncomment its block. If the project builds, the step is done.
#include <gtest/gtest.h>
#include <kalon/Dimension.hpp>
#include <type_traits>
#include <utility>

using namespace kalon;

namespace {

// "Can this expression be written?" Works in both directions:
//   static_assert(can_add<A, B>)    -> it must compile
//   static_assert(!can_add<A, B>)   -> it must NOT compile
// These must be concepts (templates). A bare requires-expression with concrete types
// inside a static_assert is a hard compile error, not "false".
template <class A, class B> concept can_add = requires(A a, B b) { a + b; };
template <class A, class B> concept can_sub = requires(A a, B b) { a - b; };
template <class A, class B> concept can_mul = requires(A a, B b) { a * b; };
template <class A, class B> concept can_div = requires(A a, B b) { a / b; };

// The type an expression produces, for checking exponent arithmetic.
template <class A, class B> using sum_t      = decltype(std::declval<A>() + std::declval<B>());
template <class A, class B> using product_t  = decltype(std::declval<A>() * std::declval<B>());
template <class A, class B> using quotient_t = decltype(std::declval<A>() / std::declval<B>());

}  // namespace

// ---- Active now: only needs the aliases that already exist ----------------------------
static_assert(!std::is_same_v<Length, Time>);
static_assert(!std::is_same_v<Length, Mass>);
static_assert(!std::is_same_v<Velocity, Acceleration>);
static_assert(!std::is_same_v<Acceleration, Force>);

TEST(Dimension, AliasesAreDistinctTypes) {
    SUCCEED();  // the static_asserts above are the test
}

// ---- STEP: same-dimension + and - ----------------------------------------------------
// The positive twin matters: without it, "Length + Time does not compile" also passes
// when no operator + exists at all.
// static_assert(can_add<Length, Length>);
// static_assert(can_sub<Length, Length>);
// static_assert(std::is_same_v<sum_t<Length, Length>, Length>);
// static_assert(!can_add<Length, Time>);
// static_assert(!can_sub<Length, Time>);
// static_assert(!can_add<Velocity, Acceleration>);

// ---- STEP: * and / add and subtract exponents ----------------------------------------
// static_assert(std::is_same_v<quotient_t<Length, Time>, Velocity>);
// static_assert(std::is_same_v<quotient_t<Velocity, Time>, Acceleration>);
// static_assert(std::is_same_v<product_t<Mass, Acceleration>, Force>);
//
// With ratio exponents these only hold if the computed exponents come out normalized,
// so this block also checks that. Open design question for you: what is the type of
// quotient_t<Length, Length>? A Dimension with all-zero exponents, or a plain Real?

// ---- STEP: unnormalized ratios ---------------------------------------------------------
// std::ratio<2,4> and std::ratio<1,2> are different types. Decide what happens if
// someone spells a dimension that way (rejected, or normalized to the same type) and
// assert it here.

// ---- STEP: the doc's free-fall example, at the type level ------------------------------
// height + v*dt must be legal (every term is a length); height + v must not be.
// static_assert(can_add<Length, product_t<Velocity, Time>>);
// static_assert(!can_add<Length, Velocity>);
