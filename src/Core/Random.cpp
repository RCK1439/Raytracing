#include "Random.hpp"

#include <glm/geometric.hpp>

#include <limits>
#include <random>

namespace rt {
    
struct RandomData final
{
    std::mt19937                        RandomEngine{};
    std::uniform_real_distribution<f32> Distribution{};
    std::random_device                  RandomDevice{};
};

static RandomData s_Data{};

f32 Random::Float()
{
    return s_Data.Distribution(s_Data.RandomEngine);
}

glm::vec3 Random::InUnitSphere()
{
    glm::vec3 point{};
        
    do
    {
        point = 2.0f * glm::vec3(Float(), Float(), Float()) - glm::vec3(1.0f);
    } while (glm::dot(point, point) >= 1.0f);

    return point;
}

glm::vec3 Random::InUnitDisk()
{
    glm::vec3 point{};

    do
    {
        point = 2.0f * glm::vec3(Float(), Float(), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
    } while (glm::dot(point, point) >= 1.0f);

    return point;
}

namespace random {

    static u32 random_state{};

    static u32 pcg_hash(u32 input) {
        const u32 state = input * 747796405u + 2891336453u;
        const u32 word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    void init(u32 seed) {
        random_state = seed;
    }
    
    f32 random_float() {
        random_state = pcg_hash(random_state);
        return static_cast<f32>(random_state) / static_cast<f32>(std::numeric_limits<u32>::max());
    }

    glm::vec3 in_unit_sphere() {
        glm::vec3 point{};
        
        do
        {
            point = 2.0f * glm::vec3(random_float(), random_float(), random_float()) - glm::vec3(1.0f);
        } while (glm::dot(point, point) >= 1.0f);

        return point;
    }

    glm::vec3 in_unit_disk() {
        glm::vec3 point{};

        do
        {
            point = 2.0f * glm::vec3(random_float(), random_float(), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
        } while (glm::dot(point, point) >= 1.0f);

        return point;
    }
}

}
