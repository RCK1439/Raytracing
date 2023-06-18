#include "Lambertian.hpp"

#include "Random.hpp"

namespace rt
{
    Lambertian::Lambertian(const glm::vec3& albedo) :
        m_Albedo(albedo, 1.0f)
    {
    }

    bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 target = record.Point + record.Normal + Random::InUnitSphere();
        scattered = { record.Point, target - record.Point };
        attenuation = m_Albedo;

        return true;
    }
} // namespace rt
