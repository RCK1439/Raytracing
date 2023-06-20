#pragma once

#include "Types.hpp"

#include <memory>

namespace rt
{
    class Sphere
    {
    public: 
        Sphere() = default;
        Sphere(const glm::vec3& position, f32 radius, Material* material);
        ~Sphere() = default;

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

    private:
        bool CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp, HitRecord& record) const;

    private:
        glm::vec3 m_Centre;
        f32 m_Radius;
        std::shared_ptr<Material> m_Material = nullptr;
    };
} // namespace rt
