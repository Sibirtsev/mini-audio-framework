#include <maf/utils/Math.h>

namespace maf::utils
{
    float dbToGain(float db)
    {
        return std::pow(10.0f, db / 20.0f);
    }

    float gainToDb(float gain)
    {
        return 20.0f * std::log10(gain);
    }

    float clamp(float value, float minValue, float maxValue)
    {
        return std::max(minValue, std::min(maxValue, value));
    }

    float lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    float mapLinear(float value, float inMin, float inMax, float outMin, float outMax)
    {
        return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));
    }
} // namespace maf::utils
