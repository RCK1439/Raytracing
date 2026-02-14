#pragma once

#include "Sphere.hpp"

#include <vector>

namespace rt {

class Scene final
{
public: 
    Scene();

    Option<HitRecord> Hit(const Ray& ray, f32 tMin, f32 tMax) const;
    
    template<typename ... Args>
    constexpr void Add(Args&& ... args)
    {
        m_Objects.emplace_back(std::forward<Args>(args)...);
    }
        
private:
    std::vector<Sphere> m_Objects;
};

}
