#include "Sphere.hpp"

#include <glm/geometric.hpp>

namespace rt
{
    bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
    {
        const glm::vec3 displacement = ray.Origin - m_Centre;

        const float a = glm::dot(ray.Direction, ray.Direction);
        const float b = glm::dot(displacement, ray.Direction);
        const float c = glm::dot(displacement, displacement) - m_Radius * m_Radius;

        const float discriminant = b * b - a * c;

        if (discriminant < 0)
            return false;

        const float root = sqrtf(discriminant);

        return CheckRoot(ray, tMin, tMax, (-b - root) / a, record) || 
               CheckRoot(ray, tMin, tMax, (-b + root) / a, record);
    }

    bool Sphere::CheckRoot(const Ray& ray, float tMin, float tMax, float temp, HitRecord& record) const
    {
        if (temp >= tMax || temp <= tMin)
            return false;

        record.t = temp;
        record.Point = ray.PointAt(temp);
        record.Normal = (record.Point - m_Centre) / m_Radius;
        record.Mat = m_Material;

        return true;
    }
}
