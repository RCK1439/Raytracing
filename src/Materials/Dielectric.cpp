#include "Dielectric.hpp"
#include "Random.hpp"

#include <glm/glm.hpp>

namespace rt
{ 
    bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 outwardNormal;
        glm::vec3 refracted = glm::vec3(0.0f);
        const glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);

        f32 niOverNT;
        f32 cosine;

        const f32 dotDirNorm = glm::dot(ray.Direction, record.Normal);
        const f32 dirLength  = 1.0f; // glm::length(ray.Direction); This will always be 1.

        if (dotDirNorm > 0.0f)
        {
            outwardNormal = -record.Normal;
            niOverNT = m_RefractiveIndex;
            cosine = m_RefractiveIndex * dotDirNorm / dirLength;
        }
        else
        {
            outwardNormal = record.Normal;
            niOverNT = 1.0f / m_RefractiveIndex;
            cosine = -dotDirNorm / dirLength;
        }

        const f32 reflectProbability = Refract(ray.Direction, outwardNormal, niOverNT, refracted) ? Schlick(cosine) : 1.0f;

        scattered   = Random::Float() < reflectProbability ? Ray{ record.Point, reflected } : Ray{ record.Point, refracted };
        attenuation = { 1.0f, 1.0f, 1.0f, 1.0f };

        return true;
    }

    bool Dielectric::Refract(const glm::vec3& v, const glm::vec3& n, f32 niOverNT, glm::vec3& refracted) const
    {
        const f32 dt = glm::dot(v, n);
        const f32 discriminant = 1.0f - niOverNT * niOverNT * (1.0f - dt * dt);

        if (discriminant > 0.0f)
        {
            refracted = niOverNT * (v - n * dt) - n * sqrtf(discriminant);
            return true;
        }

        return false;
    }

    f32 Dielectric::Schlick(f32 cosine) const
    {
        f32 r0 = (1.0f - m_RefractiveIndex) / (1.0f + m_RefractiveIndex);
        r0 = r0 * r0;

        return r0 + (1.0f - r0) * glm::pow((1 - cosine), 5);
    }
}
