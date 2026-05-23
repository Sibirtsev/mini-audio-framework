#pragma once

#include <vector>
#include <stdexcept>

namespace maf::core
{
    template <typename SampleType> 
    class OwnedAudioBuffer
    {
      public:
        OwnedAudioBuffer();
        OwnedAudioBuffer(size_t numChannels, size_t numSamples);

        void resize(size_t numCannels, size_t numSamples);

        size_t getNumChannels() const;
        size_t getNumSamples() const;

        SampleType *getWritePointer(size_t channel);
        const SampleType *getReadPointer(size_t channel) const;

        SampleType getSample(size_t channel, size_t sample) const;
        void setSample(size_t channel, size_t sample, SampleType value);

        void clear();
        void fill(SampleType value);

      private:
        size_t numChannels_ = 0;
        size_t numSamples_ = 0;
        std::vector<SampleType> data_;
        std::vector<SampleType*> channelPointers_;
    };
} // namespace maf

#include "OwnedAudioBuffer.tpp"
