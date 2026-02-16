#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace rt {

class Material;

struct HitRecord final
{
    Ref<Material> Mat{};
    glm::vec3     Point{};
    glm::vec3     Normal{};
    f32           t{};
};

}
