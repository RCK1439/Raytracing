#include "Metal.hpp"
#include "HitRecord.hpp"
#include "Random.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace rt {

Option<ScatterData> Metal::Scatter(const Ray& ray, const HitRecord& record) const
{
    const glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);
    const Ray scattered = { record.Point, reflected + m_Fuzz * Random::InUnitSphere() };
    const glm::vec4 attenuation = m_Albedo;

    if (glm::dot(scattered.Direction, record.Normal) > 0.0f)
        return ScatterData { scattered, attenuation };

    return {};
}

}
