#pragma once

#include "Sphere.hpp"

#include <vector>

namespace rt
{
    class Scene final : public Hitable
    {
    public:
        Scene();
        ~Scene() = default;

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

        void Add(const Sphere& obj);
    private:
        std::vector<Sphere> m_Objects;
    };
} // namespace rt
