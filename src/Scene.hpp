#pragma once

#include "Sphere.hpp"

#include <vector>

namespace rt
{
    class Scene
    {
    public: 
        Scene();

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;
        void Add(Sphere&& obj);
    private:
        std::vector<Sphere> m_Objects;
    };
}
