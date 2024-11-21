#pragma once

#include "Material.hpp"

#include <algorithm>

namespace rt
{
    class Metal final : public Material
    {
    public: 
        Metal(const glm::vec3& albedo, float fuzz) :
            m_Albedo(albedo, 1.0f), m_Fuzz(std::clamp(fuzz, 0.0f, 1.0f)) {}

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
        float     m_Fuzz = 0.0f;
    };
}
