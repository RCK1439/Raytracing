#pragma once

#include "Renderer/Ray.hpp"
#include "Core/Types.hpp"

#include <glm/vec4.hpp>

namespace RTIAW {

struct HitRecord;

struct ScatterData
{
    Ray       Scattered;
    glm::vec4 Attenuation;
};

class Material
{
public: 
    virtual ~Material() = default;

    virtual Option<ScatterData> Scatter(const Ray& ray, const HitRecord& record) const = 0;
};

}
