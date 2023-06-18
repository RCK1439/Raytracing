#pragma once

#include "Material.hpp"

namespace rt
{
    class Metal final : public Material
    {
    public:
        Metal(const glm::vec3& albedo, f32 fuzz);
        ~Metal() override = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
        f32 m_Fuzz = 0.0f;
    };
} // namespace rt
