#pragma once

#include <glm/vec3.hpp>

#include <memory>

namespace rt
{
    class Material;

    struct HitRecord final
    {
        std::shared_ptr<Material> Mat;
        glm::vec3                 Point;
        glm::vec3                 Normal;
        float                     t;
    };
}
