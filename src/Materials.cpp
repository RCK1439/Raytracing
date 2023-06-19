#include "Materials.hpp"
#include "Random.hpp"

#include <glm/geometric.hpp>
#include <algorithm>

namespace rt
{
    
//  ==================================================
//  Lambertian
//  ==================================================

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

//  ==================================================
//  Metal
//  ==================================================

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

//  ==================================================
//  Dielectric
//  ==================================================

    Dielectric::Dielectric(f32 refractiveIndex) :
        m_RefractiveIndex(refractiveIndex)
    {
    }

    bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const
    {
        glm::vec3 outwardNormal;
        glm::vec3 refracted;
        glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);

        f32 niOverNT;
        f32 cosine;

        const f32 dotDirNorm = glm::dot(ray.Direction, record.Normal);
        const f32 dirLength  = glm::length(ray.Direction);

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
        glm::vec3 uv = glm::normalize(v);
        
        f32 dt = glm::dot(uv, n);
        f32 discriminant = 1.0f - niOverNT * niOverNT * (1.0f - dt * dt);

        if (discriminant > 0.0f)
        {
            refracted = niOverNT * (uv - n * dt) - n * sqrtf(discriminant);
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
    
} // namespace rt
