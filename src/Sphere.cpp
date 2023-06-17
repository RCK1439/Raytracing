#include "Sphere.hpp"

#include <glm/geometric.hpp>

namespace rt
{
    Sphere::Sphere(const glm::vec3& position, f32 radius) :
        m_Centre(position), m_Radius(radius)
    {    
    }

    bool Sphere::Hit(const Ray& ray) const
    {
        glm::vec3 displacement = ray.Origin - m_Centre;

        f32 a = glm::dot(ray.Direction, ray.Direction);
        f32 b = 2.0f * glm::dot(displacement, ray.Direction);
        f32 c = glm::dot(displacement, displacement) - m_Radius * m_Radius;

        f32 discriminant = b * b - 4.0f * a * c;

        return discriminant > 0.0f;
    }
} // namespace rt
