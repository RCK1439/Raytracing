#pragma once

#include "Materials/Material.hpp"
#include "Renderer/Ray.hpp"

#include <glm/vec3.hpp>

#include <memory>

namespace rt
{
    class Sphere final
    {
    public:
        Sphere(const glm::vec3& position, float radius, Material* material) :
            m_Material(material), m_Centre(position), m_Radius(radius) {}

        bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;

    private:
        bool CheckRoot(const Ray& ray, float tMin, float tMax, float temp, HitRecord& record) const;

    private:
        std::shared_ptr<Material> m_Material = nullptr;
        glm::vec3                 m_Centre;
        float                     m_Radius;
    };
}
