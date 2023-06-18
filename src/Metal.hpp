#pragma once

#include "Material.hpp"

namespace rt
{
    class Metal final : public Material
    {
    public:
        Metal(const glm::vec3& albedo);
        ~Metal() override = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
    };
} // namespace rt
