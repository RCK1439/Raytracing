#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace RTIAW::Random {

void Init(u32 seed) noexcept;

f32 Float() noexcept;
glm::vec3 InUnitSphere() noexcept;
glm::vec3 InUnitDisk() noexcept;

}
