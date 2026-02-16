#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace rt {

class Random final
{
public:
    static f32 Float();
    static glm::vec3 InUnitSphere();
    static glm::vec3 InUnitDisk();
};

namespace random {

    void init(u32 seed);

    f32 random_float();
    glm::vec3 in_unit_sphere();
    glm::vec3 in_unit_disk();
}

}
