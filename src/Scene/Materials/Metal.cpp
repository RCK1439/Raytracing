#include "Metal.hpp"
#include "HitRecord.hpp"
#include "Random.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace rt
{
    bool Metal::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        const glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);
        scattered = { record.Point, reflected + m_Fuzz * Random::InUnitSphere() };
        attenuation = m_Albedo;

        return glm::dot(scattered.Direction, record.Normal) > 0.0f;
    }
}
