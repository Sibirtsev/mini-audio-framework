#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <maf/core/OwnedAudioBuffer.h>

TEST_CASE("OwnedAudioBuffer stores its dimensions", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 512);

    REQUIRE(buffer.getNumChannels() == 2);
    REQUIRE(buffer.getNumSamples() == 512);
}

TEST_CASE("OwnedAudioBuffer is silent after construction", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            REQUIRE(buffer.getSample(channel, sample) == 0.0f);
        }
    }
}

TEST_CASE("OwnedAudioBuffer stores individual samples", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    buffer.setSample(0, 2, 0.75f);
    buffer.setSample(1, 1, -0.5f);

    REQUIRE(buffer.getSample(0, 2) == 0.75f);
    REQUIRE(buffer.getSample(1, 1) == -0.5f);
}

TEST_CASE("OwnedAudioBuffer channels are independent", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    buffer.setSample(0, 0, 1.0f);

    REQUIRE(buffer.getSample(0, 0) == 1.0f);
    REQUIRE(buffer.getSample(1, 0) == 0.0f);
}

TEST_CASE("OwnedAudioBuffer fills every channel and sample", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    buffer.fill(0.25f);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            REQUIRE(buffer.getSample(channel, sample) == 0.25f);
        }
    }
}

TEST_CASE("OwnedAudioBuffer clears every channel and sample", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

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

TEST_CASE("OwnedAudioBuffer provides writable channel pointers", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    float *leftChannel = buffer.getWritePointer(0);
    float *rightChannel = buffer.getWritePointer(1);

    leftChannel[0] = 0.5f;
    leftChannel[1] = 0.25f;
    rightChannel[0] = -0.5f;

    REQUIRE(buffer.getSample(0, 0) == 0.5f);
    REQUIRE(buffer.getSample(0, 1) == 0.25f);
    REQUIRE(buffer.getSample(1, 0) == -0.5f);
}

TEST_CASE("OwnedAudioBuffer exposes contiguous samples inside each channel", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    float *leftChannel = buffer.getWritePointer(0);
    float *rightChannel = buffer.getWritePointer(1);

    leftChannel[3] = 0.75f;
    rightChannel[0] = -0.25f;

    REQUIRE(buffer.getSample(0, 3) == 0.75f);
    REQUIRE(buffer.getSample(1, 0) == -0.25f);
}

TEST_CASE("OwnedAudioBuffer updates dimensions after resize", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(1, 4);

    buffer.resize(2, 512);

    REQUIRE(buffer.getNumChannels() == 2);
    REQUIRE(buffer.getNumSamples() == 512);

    buffer.setSample(0, 511, 0.5f);
    buffer.setSample(1, 511, -0.5f);

    REQUIRE(buffer.getSample(0, 511) == 0.5f);
    REQUIRE(buffer.getSample(1, 511) == -0.5f);
}

TEST_CASE("OwnedAudioBuffer creates a view over its owned samples", "[core][buffer]")
{
    maf::core::OwnedAudioBuffer<float> buffer(2, 4);

    auto view = buffer.view();

    view.setSample(0, 1, 0.75f);

    REQUIRE(buffer.getSample(0, 1) == 0.75f);
}

