#pragma once

#include "Sphere.hpp"

#include <vector>

namespace RTIAW {

class Scene final
{
public: 
    Scene() noexcept;

    Option<HitRecord> Hit(const Ray& ray, f32 tMin, f32 tMax) const noexcept;
    
    template<typename ... Args>
    constexpr void Add(Args&& ... args) noexcept
    {
        m_Objects.emplace_back(std::forward<Args>(args)...);
    }
        
private:
    std::vector<Sphere> m_Objects;
};

}
