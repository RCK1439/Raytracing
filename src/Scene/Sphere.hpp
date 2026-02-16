#pragma once

#include "Core/Types.hpp"

#include "Materials/Material.hpp"

#include "Renderer/Ray.hpp"

#include <glm/vec3.hpp>

namespace RTIAW {

class Sphere final
{
public:
    Sphere(const glm::vec3& position, f32 radius, Ref<Material> material) :
        m_Material(material), m_Centre(position), m_Radius(radius) {}

    Option<HitRecord> Hit(const Ray& ray, f32 tMin, f32 tMax) const;

private:
    Option<HitRecord> CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp) const;

private:
    Ref<Material> m_Material{};
    glm::vec3     m_Centre{};
    f32           m_Radius{};
};

}
