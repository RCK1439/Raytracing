#include "HitableList.hpp"
#include "Material.hpp"

namespace rt
{
    HitableList::~HitableList()
    {
        for (auto& hitable : m_Data)
            delete hitable.m_Material;
    }

    bool HitableList::Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const
    {
        HitRecord tempRecord;

        bool hitAnything = false;
        f32 closest = tMax;
        for (const auto& hitable : m_Data)
        {
            if (hitable.Hit(ray, tMin, closest, tempRecord))
            {
                hitAnything = true;
                closest = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAnything;
    }

    void HitableList::Add(const Sphere& hitable)
    {
        m_Data.push_back(hitable);
    }
} // namespace rt
