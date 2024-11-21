#pragma once

#include <glm/vec3.hpp>

#include <memory>

namespace rt
{
    class Material;

    struct HitRecord
    {
        float                     t;
        glm::vec3                 Point;
        glm::vec3                 Normal;
        std::shared_ptr<Material> Mat;
    };

    struct Ray
    {
        glm::vec3 Origin;
        glm::vec3 Direction;

        inline glm::vec3 PointAt(float t) const { return Origin + t * Direction; }
    };
}
