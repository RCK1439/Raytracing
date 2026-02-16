#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace rt::random {

void Init(u32 seed);

f32 Float();
glm::vec3 InUnitSphere();
glm::vec3 InUnitDisk();

}
