#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <maf/utils/Math.h>


TEST_CASE("dbToGain") {
    REQUIRE(maf::utils::dbToGain(0.0f) == Catch::Approx(1.0f).epsilon(0.01));
    REQUIRE(maf::utils::dbToGain(-6.0f) == Catch::Approx(0.501f).epsilon(0.01));
    REQUIRE(maf::utils::dbToGain(-std::numeric_limits<float>::infinity()) == Catch::Approx(0.0f));
}

TEST_CASE("gainToDb")
{
    REQUIRE(maf::utils::gainToDb(1.0f) == Catch::Approx(0.0f).epsilon(0.01));
    REQUIRE(maf::utils::gainToDb(0.5f) == Catch::Approx(-6.0f).epsilon(0.01));
    REQUIRE(maf::utils::gainToDb(0.0f) == Catch::Approx(-std::numeric_limits<float>::infinity()));
}

TEST_CASE("clamp")
{
    REQUIRE(maf::utils::clamp(2.0f, 0.0f, 1.0f) == 1.0f);
    REQUIRE(maf::utils::clamp(5.0f, 0.0f, 10.0f) == 5.0f);
    REQUIRE(maf::utils::clamp(-1.0f, 0.0f, 10.0f) == 0.0f);
    REQUIRE(maf::utils::clamp(11.0f, 0.0f, 10.0f) == 10.0f);
}

TEST_CASE("lerp")
{
    REQUIRE(maf::utils::lerp(0.0f, 10.0f, 0.0f) == 0.0f);
    REQUIRE(maf::utils::lerp(0.0f, 10.0f, 1.0f) == 10.0f);
    REQUIRE(maf::utils::lerp(0.0f, 10.0f, 0.5f) == 5.0f);
}

TEST_CASE("mapLinear")
{
    REQUIRE(maf::utils::mapLinear(5.0f, 0.0f, 10.0f, 0.0f, 100.0f) == 50.0f);
    REQUIRE(maf::utils::mapLinear(0.0f, 0.0f, 10.0f, 0.0f, 100.0f) == 0.0f);
    REQUIRE(maf::utils::mapLinear(10.0f, 0.0f, 10.0f, 0.0f, 100.0f) == 100.0f);
}
