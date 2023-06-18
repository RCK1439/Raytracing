#include "Random.hpp"

#include <random>

namespace rt
{
    struct RandomData
    {
        std::random_device                    RandomDevice;
        std::mt19937                          RandomEngine;
        std::uniform_real_distribution<float> Distribution;
    };

    static RandomData s_Data;

    void Random::Init()
    {
        s_Data.RandomEngine = std::mt19937(s_Data.RandomDevice());
        s_Data.Distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }

    f32 Random::Float()
    {
        return s_Data.Distribution(s_Data.RandomEngine);
    }
} // namespace rt
