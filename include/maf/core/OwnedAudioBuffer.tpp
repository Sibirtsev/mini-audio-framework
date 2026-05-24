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
        assert(channel < numChannels_);
        return channelPointers_[channel];
    }
   
    template <typename SampleType>
    const SampleType* OwnedAudioBuffer<SampleType>::getReadPointer(size_t channel) const
    {
        assert(channel < numChannels_);
        return channelPointers_[channel];
    }

    template <typename SampleType>
    SampleType OwnedAudioBuffer<SampleType>::getSample(size_t channel, size_t sample) const
    {
        assert(channel < numChannels_ && sample < numSamples_);

        return channelPointers_[channel][sample];
    }

    template <typename SampleType>
    void OwnedAudioBuffer<SampleType>::setSample(size_t channel, size_t sample, SampleType value)
    {
        assert(channel < numChannels_ && sample < numSamples_);

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

    template <typename SampleType> 
    AudioBufferView<SampleType> OwnedAudioBuffer<SampleType>::view()
    {
        return AudioBufferView<SampleType>(channelPointers_.data(), numChannels_, numSamples_);
    }
    
} // namespace maf
