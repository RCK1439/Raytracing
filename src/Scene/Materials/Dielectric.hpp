#pragma once

#include "Material.hpp"

#include "Core/Types.hpp"

namespace RTIAW {

class Dielectric final : public Material
{
public: 
    constexpr Dielectric(f32 refractiveIndex) noexcept :
        m_RefractiveIndex(refractiveIndex) {}

    Option<ScatterData> Scatter(const Ray& ray, const HitRecord& record) const noexcept override;

private: 
    bool Refract(const glm::vec3& v, const glm::vec3& n, f32 niOverNT, glm::vec3& refracted) const noexcept;

    f32 Schlick(f32 cosine) const noexcept;

private:
    f32 m_RefractiveIndex{};
};

}
