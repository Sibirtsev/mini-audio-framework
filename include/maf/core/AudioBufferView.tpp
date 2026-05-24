#include <maf/core/AudioBufferView.h>

namespace maf::core
{
    template <typename SampleType>
    AudioBufferView<SampleType>::AudioBufferView(
        SampleType *const *channels,
        std::size_t numChannels,
        std::size_t numSamples
    ) : channels_(channels), 
        numChannels_(numChannels), 
        numSamples_(numSamples)
    {
        assert(channels != nullptr);
        assert(numChannels > 0 && numSamples > 0);
        for (std::size_t i = 0; i < numChannels; ++i)
        {
            assert(channels[i] != nullptr);
        }
    }

    template <typename SampleType>
    std::size_t AudioBufferView<SampleType>::getNumChannels() const noexcept
    {
        return numChannels_;
    }

    template <typename SampleType> 
    std::size_t AudioBufferView<SampleType>::getNumSamples() const noexcept
    {
        return numSamples_;
    }

    template <typename SampleType>
    SampleType *
    AudioBufferView<SampleType>::getWritePointer(std::size_t channel) noexcept
    {
        assert(channel < numChannels_);

        return channels_[channel];
    }

    template <typename SampleType>
    const SampleType *
    AudioBufferView<SampleType>::getReadPointer(std::size_t channel) const noexcept
    {
        assert(channel < numChannels_);

        return channels_[channel];
    }

    template <typename SampleType>
    SampleType AudioBufferView<SampleType>::getSample(
        std::size_t channel, 
        std::size_t sampleIndex) const noexcept
    {
        assert(channel < numChannels_ && sampleIndex < numSamples_);

        return channels_[channel][sampleIndex];
    }

    template <typename SampleType>
    void AudioBufferView<SampleType>::setSample(
        std::size_t channel, 
        std::size_t sampleIndex, 
        SampleType value) noexcept
    {
        assert(channel < numChannels_ && sampleIndex < numSamples_);

        channels_[channel][sampleIndex] = value;
    }

    template <typename SampleType> 
    void AudioBufferView<SampleType>::clear() noexcept
    {
        for (std::size_t i = 0; i < numChannels_; ++i)
        {
            std::fill(channels_[i], channels_[i] + numSamples_, SampleType{});
        }
    }

    template <typename SampleType> 
    void AudioBufferView<SampleType>::fill(SampleType value) noexcept
    {
        for (std::size_t i = 0; i < numChannels_; ++i)
        {
            std::fill(channels_[i], channels_[i] + numSamples_, value);
        }
    }

} // namespace maf::core