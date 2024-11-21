#pragma once

#include "Material.hpp"

namespace rt
{ 
    class Dielectric final : public Material
    {
    public: 
        Dielectric(float refractiveIndex) :
            m_RefractiveIndex(refractiveIndex) {}

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private: 
        bool Refract(const glm::vec3& v, const glm::vec3& n, float niOverNT, glm::vec3& refracted) const;

        float Schlick(float cosine) const;

    private:
        float m_RefractiveIndex;
    };
}
