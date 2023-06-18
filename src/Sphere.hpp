#pragma once

#include "Hitable.hpp"

#include <glm/vec3.hpp>

namespace rt
{
    class Sphere final : public Hitable
    {
    public: 
        Sphere() = default;
        Sphere(const glm::vec3& position, f32 radius, Material* material);
        ~Sphere();

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const override;

    private:
        bool CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp, HitRecord& record) const;

    private:
        glm::vec3 m_Centre;
        f32 m_Radius;
        Material* m_Material = nullptr;
    };
} // namespace rt
