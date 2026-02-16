#include "Random.hpp"

#include <glm/geometric.hpp>

#include <limits>

namespace rt::random {

static u32 s_RandomState{};

inline constexpr u32 PCGHash(u32 input)
{
    const u32 state = input * 747796405u + 2891336453u;
    const u32 word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

void Init(u32 seed)
{
    s_RandomState = seed;
}
    
f32 Float()
{
    s_RandomState = PCGHash(s_RandomState);
    return static_cast<f32>(s_RandomState) / static_cast<f32>(std::numeric_limits<u32>::max());
}

glm::vec3 InUnitSphere()
{
    glm::vec3 point{};
    
    do
    {
        point = 2.0f * glm::vec3(Float(), Float(), Float()) - glm::vec3(1.0f);
    } while (glm::dot(point, point) >= 1.0f);

    return point;
}

glm::vec3 InUnitDisk()
{
    glm::vec3 point{};

    do
    {
        point = 2.0f * glm::vec3(Float(), Float(), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
    } while (glm::dot(point, point) >= 1.0f);

    return point;
}

}
