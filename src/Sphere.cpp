#include "Sphere.hpp"
#include "Material.hpp"

#include <glm/geometric.hpp>

namespace rt
{
    Sphere::Sphere(const glm::vec3& position, f32 radius, Material* material) :
        m_Centre(position), m_Radius(radius), m_Material(material)
    {    
    }

    Sphere::~Sphere()
    {
        delete m_Material;
    }

    bool Sphere::Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const
    {
        const glm::vec3 displacement = ray.Origin - m_Centre;

        const f32 a = glm::dot(ray.Direction, ray.Direction);
        const f32 b = glm::dot(displacement, ray.Direction);
        const f32 c = glm::dot(displacement, displacement) - m_Radius * m_Radius;

        const f32 discriminant = b * b - a * c;

        if (discriminant < 0)
            return false;

        const f32 root = sqrtf(discriminant);

        return CheckRoot(ray, tMin, tMax, (-b - root) / a, record) || 
               CheckRoot(ray, tMin, tMax, (-b + root) / a, record);
    }

    bool Sphere::CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp, HitRecord& record) const
    {
        if (temp >= tMax || temp <= tMin)
            return false;

        record.t      = temp;
        record.Point  = ray.PointAt(temp);
        record.Normal = (record.Point - m_Centre) / m_Radius;
        record.Mat    = m_Material;

        return true;
    }
} // namespace rt
