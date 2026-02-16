#pragma once

#include "Core/Types.hpp"

#include <glm/vec3.hpp>

namespace rt {

class Random final
{
public: 
    static void Init();
    
    static f32 Float();
    static glm::vec3 InUnitSphere();
    static glm::vec3 InUnitDisk();
};

}
