#include "Sphere.hpp"

#include <glm/geometric.hpp>

namespace rt
{
    Sphere::Sphere(const glm::vec3& position, f32 radius) :
        m_Centre(position), m_Radius(radius)
    {    
    }

    bool Sphere::Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const
    {
        glm::vec3 displacement = ray.Origin - m_Centre;

        f32 a = glm::dot(ray.Direction, ray.Direction);
        f32 b = glm::dot(displacement, ray.Direction);
        f32 c = glm::dot(displacement, displacement) - m_Radius * m_Radius;

        f32 discriminant = b * b - a * c;

        if (discriminant < 0)
            return false;

        const f32 root = sqrtf(b * b - a * c);

        f32 temp = (-b - root) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.Point = ray.PointAt(temp);
            record.Normal = (record.Point - m_Centre) / m_Radius;

            return true;
        }

        temp = (-b + root) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.Point = ray.PointAt(temp);
            record.Normal = (record.Point - m_Centre) / m_Radius;

            return true;
        }

        return false;
    }
} // namespace rt
