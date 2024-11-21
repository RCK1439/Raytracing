#pragma once

#include "Types.hpp"
#include "Materials/Material.hpp"

#include <memory>

namespace rt
{
    class Sphere
    {
    public:
        Sphere(const glm::vec3& position, f32 radius, Material* material) :
            m_Centre(position), m_Radius(radius), m_Material(material) {}

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

    private:
        bool CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp, HitRecord& record) const;

    private:
        glm::vec3                 m_Centre;
        f32                       m_Radius;
        std::shared_ptr<Material> m_Material = nullptr;
    };
}
