#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <maf/core/AudioBufferView.h>

TEST_CASE("AudioBufferView stores its dimensions", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};

    maf::core::AudioBufferView<float> buffer(channels, 2, 4);
    
    REQUIRE(buffer.getNumChannels() == 2);
    REQUIRE(buffer.getNumSamples() == 4);
}

TEST_CASE("AudioBufferView reads individual samples", "[core][buffer]")
{
    float channel1[4] = {0.1f, 0.2f, 0.3f, 0.4f};
    float channel2[4] = {-0.1f, -0.2f, -0.3f, -0.4f};
    
    float *const channels[] = {channel1, channel2};

    maf::core::AudioBufferView<float> buffer(channels, 2, 4);

    REQUIRE(buffer.getSample(0, 2) == 0.3f);
    REQUIRE(buffer.getSample(1, 1) == -0.2f);
}

TEST_CASE("AudioBufferView stores individual samples", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};

    float *const channels[] = {channel1, channel2};
    
    maf::core::AudioBufferView<float> buffer(channels, 2, 4);
    
    buffer.setSample(0, 1, 0.75f);

    REQUIRE(buffer.getSample(0, 1) == 0.75f);
    REQUIRE(channel1[1] == 0.75f);
}

TEST_CASE("AudioBufferView write pointer provides direct access to channel data", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};

    maf::core::AudioBufferView<float> buffer(channels, 2, 4);

    buffer.getWritePointer(1)[0] = 3.0f;

    REQUIRE(channel1[0] == 0.0f);
    REQUIRE(channel2[0] == 3.0f);
}

TEST_CASE("AudioBufferView read pointer provides direct access to channel data", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};
    
    maf::core::AudioBufferView<float> buffer(channels, 2, 4);
    
    buffer.getWritePointer(0)[2] = 1.5f;
    const float *readPtr = buffer.getReadPointer(0);

    REQUIRE(readPtr[2] == 1.5f);
}

TEST_CASE("AudioBufferView channels are independent", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};
    maf::core::AudioBufferView<float> buffer(channels, 2, 4);
    buffer.setSample(0, 0, 1.0f);
    REQUIRE(buffer.getSample(0, 0) == 1.0f);
    REQUIRE(buffer.getSample(1, 0) == 0.0f);
}

TEST_CASE("AudioBufferView fills every channel and sample", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};
    maf::core::AudioBufferView<float> buffer(channels, 2, 4);
    
    buffer.fill(0.25f);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            REQUIRE(buffer.getSample(channel, sample) == 0.25f);
        }
    }
}

TEST_CASE("AudioBufferView clears every channel and sample", "[core][buffer]")
{
    float channel1[4] = {0.0f};
    float channel2[4] = {0.0f};
    float *const channels[] = {channel1, channel2};
    
    maf::core::AudioBufferView<float> buffer(channels, 2, 4);

    buffer.fill(0.75f);
    buffer.clear();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            REQUIRE(buffer.getSample(channel, sample) == 0.0f);
        }
    }
}

