#pragma once

#include "Types.hpp"

namespace rt
{
    class Random
    {
    public:
        static void Init();

        static f32 Float();
        static glm::vec3 InUnitSphere();
    };
} // namespace rt
