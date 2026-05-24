#pragma once

namespace maf::realtime
{
    class ScopedNoDenormals
    {
      public:
        ScopedNoDenormals() noexcept;
        ~ScopedNoDenormals() noexcept;

        ScopedNoDenormals(const ScopedNoDenormals &) = delete;
        ScopedNoDenormals &operator=(const ScopedNoDenormals &) = delete;

      private:
        unsigned int previousControlWord_ = 0;
    };
} // namespace maf::realtime