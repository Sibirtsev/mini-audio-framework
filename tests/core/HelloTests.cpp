#include <catch2/catch_test_macros.hpp>

#include <maf/core/Hello.h>

TEST_CASE("Hello")
{
    REQUIRE(maf::core::hello() == "hello");
}