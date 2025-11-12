#include <gtest/gtest.h>

#include "kalon/kalon.hpp"

TEST(KalonBasics, AddsNumbers) {
    EXPECT_EQ(kalon::add(1, 2), 3);
}

TEST(KalonBasics, ReportsVersion) {
    EXPECT_EQ(kalon::Version::string(), "0.1.0");
}
