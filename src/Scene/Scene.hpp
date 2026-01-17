#pragma once

#include "Sphere.hpp"

#include <vector>

namespace rt {

class Scene final
{
public: 
    Scene();

    Option<HitRecord> Hit(const Ray& ray, f32 tMin, f32 tMax) const;
    void Add(Sphere&& obj);
        
private:
    std::vector<Sphere> m_Objects;
};

}
