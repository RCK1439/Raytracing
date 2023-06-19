#pragma once

#include "Material.hpp"

namespace rt
{

//  ==================================================
//  Lambertian
//  ==================================================

    class Lambertian final : public Material
    {
    public:
        Lambertian(const glm::vec3& albedo);
        ~Lambertian() override = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
    };

//  ==================================================
//  Metal
//  ==================================================

    class Metal final : public Material
    {
    public:
        Metal(const glm::vec3& albedo, f32 fuzz);
        ~Metal() override = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
        f32 m_Fuzz = 0.0f;
    };

//  ==================================================
//  Dielectric
//  ==================================================

    class Dielectric final : public Material
    {
    public:
        Dielectric(f32 refractiveIndex);
        ~Dielectric() override = default;

        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        bool Refract(const glm::vec3& v, const glm::vec3& n, f32 niOverNT, glm::vec3& refracted) const;
        f32 Schlick(f32 cosine) const;

    private:
        f32 m_RefractiveIndex;
    };

} // namespace rt
