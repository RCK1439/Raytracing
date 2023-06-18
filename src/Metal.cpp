#include "Metal.hpp"
#include "Random.hpp"

#include <glm/geometric.hpp>
#include <algorithm>

namespace rt
{
    Metal::Metal(const glm::vec3& albedo, f32 fuzz) :
        m_Albedo(albedo, 1.0f), m_Fuzz(fuzz)
    {
        std::clamp(m_Fuzz, 0.0f, 1.0f);
    }

    bool Metal::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 reflected = glm::reflect(glm::normalize(ray.Direction), record.Normal);
        scattered = { record.Point, reflected + m_Fuzz * Random::InUnitSphere() };
        attenuation = m_Albedo;

        return glm::dot(scattered.Direction, record.Normal) > 0.0f;
    }
} // namespace rt
