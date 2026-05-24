#pragma once
#include <cassert>

namespace maf::core
{
    template <typename SampleType> 
    class AudioBufferView
    {
      public:
        AudioBufferView() = delete;

        AudioBufferView(SampleType *const *channels, 
            std::size_t numChannels, 
            std::size_t numSamples
        );

        std::size_t getNumChannels() const noexcept;
        std::size_t getNumSamples() const noexcept;

        SampleType *getWritePointer(std::size_t channel) noexcept;
        const SampleType *getReadPointer(std::size_t channel) const noexcept;

        SampleType getSample(
            std::size_t channel, 
            std::size_t sampleIndex
        ) const noexcept;
        
        void setSample(
            std::size_t channel, 
            std::size_t sampleIndex, 
            SampleType value) noexcept;

        void clear() noexcept;
        void fill(SampleType value) noexcept;

      private:
        SampleType *const *channels_ = nullptr;
        std::size_t numChannels_ = 0;
        std::size_t numSamples_ = 0;
    };
} // namespace maf::core

#include "AudioBufferView.tpp"
