#pragma once

#include <glm/glm.hpp>

namespace rt
{
    class Random
    {
    public: 
        static void Init();

        static float Float();
        static glm::vec3 InUnitSphere();
        static glm::vec3 InUnitDisk();
    };
}
