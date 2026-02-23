#pragma once 

#include "Material.hpp"

namespace RTIAW {

class Lambertian final : public Material
{
public:
    Lambertian(const glm::vec3& albedo) noexcept :
        m_Albedo(albedo, 1.0f) {};

    Option<ScatterData> Scatter(const Ray& ray, const HitRecord& record) const noexcept override;

private:
    glm::vec4 m_Albedo{};
};

}
