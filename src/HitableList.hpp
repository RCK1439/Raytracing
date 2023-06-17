#pragma once

#include "Hitable.hpp"

#include <vector>

namespace rt
{
    class HitableList final : public Hitable
    {
    public:
        HitableList() = default;
        ~HitableList() = default;

        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

        void Add(Hitable* hitable);
    private:
        std::vector<Hitable*> m_Data;
    };
} // namespace rt
