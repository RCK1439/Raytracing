#include "Metal.hpp"

#include <glm/geometric.hpp>

namespace rt
{
    Metal::Metal(const glm::vec3& albedo) :
        m_Albedo(albedo, 1.0f)
    {
    }

    bool Metal::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 reflected = glm::reflect(glm::normalize(ray.Direction), record.Normal);
        scattered = { record.Point, reflected };
        attenuation = m_Albedo;

        return glm::dot(scattered.Direction, record.Normal) > 0.0f;
    }
} // namespace rt
