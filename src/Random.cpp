#include "Random.hpp"

#include <glm/geometric.hpp>

#include <random>

namespace rt
{
    struct RandomData final
    {
        std::random_device                    RandomDevice;
        std::mt19937                          RandomEngine;
        std::uniform_real_distribution<float> Distribution;
    };

    static thread_local RandomData s_Data;

    void Random::Init()
    {
        s_Data.RandomEngine = std::mt19937(s_Data.RandomDevice());
        s_Data.Distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }

    float Random::Float()
    {
        return s_Data.Distribution(s_Data.RandomEngine);
    }

    glm::vec3 Random::InUnitSphere()
    {
        glm::vec3 point;
        do
        {
            point = 2.0f * glm::vec3(Float(), Float(), Float()) - glm::vec3(1.0f);
        } while (glm::dot(point, point) >= 1.0f);

        return point;
    }

    glm::vec3 Random::InUnitDisk()
    {
        glm::vec3 point;
        do
        {
            point = 2.0f * glm::vec3(Float(), Float(), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
        } while (glm::dot(point, point) >= 1.0f);

        return point;
    }
}
