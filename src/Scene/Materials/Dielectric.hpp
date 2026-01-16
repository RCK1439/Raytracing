#pragma once

#include "Material.hpp"

#include "Types.hpp"

namespace rt {

class Dielectric final : public Material
{
public: 
    Dielectric(f32 refractiveIndex) :
        m_RefractiveIndex(refractiveIndex) {}

    bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

private: 
    bool Refract(const glm::vec3& v, const glm::vec3& n, f32 niOverNT, glm::vec3& refracted) const;

    f32 Schlick(f32 cosine) const;

private:
    f32 m_RefractiveIndex{};
};

}
