#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <limits>

#include <maf/realtime/ScopedNoDenormals.h>

#if defined(_MSC_VER) && defined(_M_X64)
    #include <xmmintrin.h>
#else
    #error "ScopedNoDenormals is currently implemented only for MSVC x64"
#endif

namespace
{
    constexpr unsigned int flushToZeroMask = 1u << 15;
    constexpr unsigned int denormalsAreZeroMask = 1u << 6;
} // namespace

TEST_CASE("ScopedNoDenormals should set and restore the control word")
{
    unsigned int controlWord = _mm_getcsr();

    {
        maf::realtime::ScopedNoDenormals noDenormals;

        unsigned int controlWordInsideScope = _mm_getcsr();

        REQUIRE((controlWordInsideScope & flushToZeroMask) != 0);
        REQUIRE((controlWordInsideScope & denormalsAreZeroMask) != 0);
    }

    REQUIRE(_mm_getcsr() == controlWord);
} 


TEST_CASE("ScopedNoDenormals should flush denormals to zero")
{
    float denormal = std::numeric_limits<float>::denorm_min();

    REQUIRE(denormal != 0.0f);
    {
        maf::realtime::ScopedNoDenormals noDenormals;
        float flushedValue = denormal * denormal;
        REQUIRE(flushedValue == 0.0f);
    }
}

TEST_CASE("ScopedNoDenormals should restore control word after scope")
{
    unsigned int initialControlWord = _mm_getcsr();
    
    {
        maf::realtime::ScopedNoDenormals noDenormals;
        unsigned int controlWordInsideScope = _mm_getcsr();

        {
            maf::realtime::ScopedNoDenormals nestedNoDenormals;
            unsigned int controlWordInsideNestedScope = _mm_getcsr();

            REQUIRE((controlWordInsideNestedScope & flushToZeroMask) != 0);
            REQUIRE((controlWordInsideNestedScope & denormalsAreZeroMask) != 0);
        }

        REQUIRE(_mm_getcsr() == controlWordInsideScope);
    }

    REQUIRE(_mm_getcsr() == initialControlWord);
}
