#pragma once

#include "Types.hpp"

#include <glm/vec4.hpp>

namespace rt
{
    struct HitRecord;
    
    class Material
    {
    public:
        virtual bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const = 0;
    };
} // namespace rt
