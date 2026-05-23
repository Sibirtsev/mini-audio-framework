#include <maf/core/OwnedAudioBuffer.h>

namespace maf::core
{
    template <typename SampleType>
    OwnedAudioBuffer<SampleType>::OwnedAudioBuffer()
    {
    }

    template <typename SampleType>
    OwnedAudioBuffer<SampleType>::OwnedAudioBuffer(size_t numChannels, size_t numSamples)
    {
        resize(numChannels, numSamples);
    }

    template <typename SampleType>
    size_t OwnedAudioBuffer<SampleType>::getNumChannels() const
    {
        return numChannels_;
    }

    template <typename SampleType>
    size_t OwnedAudioBuffer<SampleType>::getNumSamples() const
    {
        return numSamples_;
    }

    template <typename SampleType>
    void OwnedAudioBuffer<SampleType>::resize(size_t numChannels, size_t numSamples)
    {
        this->numChannels_ = numChannels;
        this->numSamples_ = numSamples;

        data_.resize(numChannels * numSamples);
        channelPointers_.resize(numChannels);
        
        for (size_t i = 0; i < numChannels; ++i)
        {
            channelPointers_[i] = &data_[i * numSamples];
        }
    }

    template <typename SampleType>
    SampleType* OwnedAudioBuffer<SampleType>::getWritePointer(size_t channel)
    {
        if (channel >= numChannels_)
        {
            throw std::out_of_range("Channel index out of range");
        }
        return channelPointers_[channel];
    }
   
    template <typename SampleType>
    const SampleType* OwnedAudioBuffer<SampleType>::getReadPointer(size_t channel) const
    {
        if (channel >= numChannels_)
        {
            throw std::out_of_range("Channel index out of range");
        }
        return channelPointers_[channel];
    }

    template <typename SampleType>
    SampleType OwnedAudioBuffer<SampleType>::getSample(size_t channel, size_t sample) const
    {
        if (channel >= numChannels_ || sample >= numSamples_)
        {
            throw std::out_of_range("Channel or sample index out of range");
        }

        return channelPointers_[channel][sample];
    }

    template <typename SampleType>
    void OwnedAudioBuffer<SampleType>::setSample(size_t channel, size_t sample, SampleType value)
    {
        if (channel >= numChannels_ || sample >= numSamples_)
        {
            throw std::out_of_range("Channel or sample index out of range");
        }

        channelPointers_[channel][sample] = value;
    }

    template <typename SampleType>
    void OwnedAudioBuffer<SampleType>::clear()
    {
        std::fill(data_.begin(), data_.end(), static_cast<SampleType>(0));
    }


    template <typename SampleType>
    void OwnedAudioBuffer<SampleType>::fill(SampleType value)
    {
        std::fill(data_.begin(), data_.end(), value);
    }
    
} // namespace maf