#pragma once

#include <algorithm>
#include <cmath>

namespace maf::utils
{
    float dbToGain(float db);
    float gainToDb(float gain);
    float clamp(float value, float minValue, float maxValue);
    float lerp(float a, float b, float t);
    float mapLinear(float value, float inMin, float inMax, float outMin, float outMax);
} // namespace maf::utils