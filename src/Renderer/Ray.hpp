#pragma once

#include <glm/vec3.hpp>

namespace rt
{
    struct Ray final
    {
        glm::vec3 Origin;
        glm::vec3 Direction;

        inline glm::vec3 PointAt(float t) const { return Origin + t * Direction; }
    };
}
