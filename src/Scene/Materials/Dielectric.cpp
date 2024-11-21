#include "Dielectric.hpp"
#include "HitRecord.hpp"
#include "Random.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace rt
{ 
    bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 outwardNormal;
        glm::vec3 refracted = glm::vec3(0.0f);
        const glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);

        float niOverNT;
        float cosine;

        const float dotDirNorm = glm::dot(ray.Direction, record.Normal);
        const float dirLength  = 1.0f; // glm::length(ray.Direction); This will always be 1.

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

        const float reflectProbability = Refract(ray.Direction, outwardNormal, niOverNT, refracted) ? Schlick(cosine) : 1.0f;

        scattered   = Random::Float() < reflectProbability ? Ray{ record.Point, reflected } : Ray{ record.Point, refracted };
        attenuation = { 1.0f, 1.0f, 1.0f, 1.0f };

        return true;
    }

    bool Dielectric::Refract(const glm::vec3& v, const glm::vec3& n, float niOverNT, glm::vec3& refracted) const
    {
        const float dt = glm::dot(v, n);
        const float discriminant = 1.0f - niOverNT * niOverNT * (1.0f - dt * dt);

        if (discriminant > 0.0f)
        {
            refracted = niOverNT * (v - n * dt) - n * sqrtf(discriminant);
            return true;
        }

        return false;
    }

    float Dielectric::Schlick(float cosine) const
    {
        float r0 = (1.0f - m_RefractiveIndex) / (1.0f + m_RefractiveIndex);
        r0 = r0 * r0;

        return r0 + (1.0f - r0) * glm::pow((1 - cosine), 5);
    }
}
