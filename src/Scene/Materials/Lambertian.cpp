#include "Lambertian.hpp"
#include "HitRecord.hpp"
#include "Random.hpp"

namespace rt
{
    bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        (void)ray;
        const glm::vec3 target = record.Point + record.Normal + Random::InUnitSphere();
        scattered = { record.Point, target - record.Point };
        attenuation = m_Albedo;

        return true;
    }
}
