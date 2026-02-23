#pragma once

#include "Core/Types.hpp"

#include "Renderer/Ray.hpp"

#include <glm/vec4.hpp>

namespace RTIAW {

struct HitRecord;

struct ScatterData final
{
    Ray       Scattered;
    glm::vec4 Attenuation;
};

class Material
{
public: 
    virtual ~Material() noexcept = default;

    virtual Option<ScatterData> Scatter(const Ray& ray, const HitRecord& record) const noexcept = 0;
};

}
