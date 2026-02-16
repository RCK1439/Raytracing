#include "Lambertian.hpp"
#include "HitRecord.hpp"

#include "Core/Random.hpp"

namespace rt {

Option<ScatterData> Lambertian::Scatter(const Ray& ray, const HitRecord& record) const
{
    (void)ray;

    const glm::vec3 target = record.Point + record.Normal + random::InUnitSphere();
    const Ray scattered = { record.Point, target - record.Point };
    const glm::vec4 attenuation = m_Albedo;

    return ScatterData { scattered, attenuation };
}

}
