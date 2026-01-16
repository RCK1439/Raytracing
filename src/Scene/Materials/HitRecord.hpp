#pragma once

#include "Types.hpp"

#include <glm/vec3.hpp>

#include <memory>

namespace rt {

class Material;

struct HitRecord final
{
    std::shared_ptr<Material> Mat{};
    glm::vec3                 Point{};
    glm::vec3                 Normal{};
    f32                       t{};
};

}
