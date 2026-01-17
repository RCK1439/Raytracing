#include "Sphere.hpp"
#include "Materials/HitRecord.hpp"

#include <glm/geometric.hpp>

namespace rt {

Option<HitRecord> Sphere::Hit(const Ray& ray, f32 tMin, f32 tMax) const
{
    const glm::vec3 displacement = ray.Origin - m_Centre;

    const f32 a = glm::dot(ray.Direction, ray.Direction);
    const f32 b = glm::dot(displacement, ray.Direction);
    const f32 c = glm::dot(displacement, displacement) - m_Radius * m_Radius;

    const f32 discriminant = b * b - a * c;

    if (discriminant < 0)
        return {};

    const f32 root = sqrtf(discriminant);

    if (const auto pHit = CheckRoot(ray, tMin, tMax, (-b - root) / a))
        return pHit.value();
    else if (const auto nHit = CheckRoot(ray, tMin, tMax, (-b + root) / a))
        return nHit.value();

    return {};
}

Option<HitRecord> Sphere::CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp) const
{
    if (temp >= tMax || temp <= tMin)
        return {};

    const glm::vec3 point = ray.PointAt(temp);
    return HitRecord {
        .Mat = m_Material,
        .Point = point,
        .Normal = (point - m_Centre) / m_Radius,
        .t = temp,
    };
}

}
