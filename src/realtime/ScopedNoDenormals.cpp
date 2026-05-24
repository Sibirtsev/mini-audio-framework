#include <maf/realtime/ScopedNoDenormals.h>

#include <iostream>
#include <bitset>


#if defined(_MSC_VER) && defined(_M_X64)
    #include <xmmintrin.h>
#else
    #error "ScopedNoDenormals is currently implemented only for MSVC x64"
// TODO:: Implement for other platforms and compilers, e.g. using fenv.h on GCC/Clang
#endif

namespace maf::realtime
{
    namespace
    {
        constexpr unsigned int flushToZeroMask = 1u << 15;
        constexpr unsigned int denormalsAreZeroMask = 1u << 6;
    } // namespace

    ScopedNoDenormals::ScopedNoDenormals() noexcept
    {
        // MSVC + x64
        previousControlWord_ = _mm_getcsr();

        auto newControlWord = previousControlWord_ | flushToZeroMask | denormalsAreZeroMask;

        _mm_setcsr(newControlWord);
    }

    ScopedNoDenormals::~ScopedNoDenormals() noexcept
    {
        // MSVC + x64
        _mm_setcsr(previousControlWord_);
    }
} // namespace maf::realtime
