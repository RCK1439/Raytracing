#pragma once

#include "Material.hpp"

namespace rt
{
    class Lambertian final : public Material
    {
    public:
        Lambertian(const glm::vec3& albedo);
        ~Lambertian() = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
    };
} // namespace rt
