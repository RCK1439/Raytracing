#pragma once

#include "Types.hpp"

namespace rt
{
    class Hitable
    {
    public: 
        virtual bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const = 0;
    };
} // namespace rt
