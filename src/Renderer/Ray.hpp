#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace rt {

struct Ray final
{
    glm::vec3 Origin{};
    glm::vec3 Direction{};

    constexpr glm::vec3 PointAt(f32 t) const { return Origin + t * Direction; }
};

}
