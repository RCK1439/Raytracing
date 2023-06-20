/**
 * Ruan C. Keet (2023)
 * Materials.hpp
*/

#pragma once

#include "Material.hpp"

namespace rt
{

//  ==================================================
//  Lambertian
//  ==================================================

    /**
     * Defines a matte material.
    */
    class Lambertian final : public Material
    {
    public:
        /**
         * Constructs a new matte material.
         * 
         * \param albedo    The color of the material.
        */
        Lambertian(const glm::vec3& albedo);

        /**
         * Destroys the material.
        */
        ~Lambertian() override = default;

        /**
         * Scatters the ray if it has been hit.
         * 
         * \param ray           The incoming ray.
         * \param record        The hit information of the ray.
         * \param attenuation   The added color value of the ray.
         * \param scattered     The outgoing scattered ray.
         * 
         * \return true, if the ray has been scattered.
        */
        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
    };

//  ==================================================
//  Metal
//  ==================================================

    /**
     * Defines a metal material.
    */
    class Metal final : public Material
    {
    public:
        /**
         * Constructs a new metal material.
         * 
         * \param albedo    The color of the material.
         * \param fuzz      The reflective muffling level of the metal. 
        */
        Metal(const glm::vec3& albedo, f32 fuzz);

        /**
         * Destroys the material.
        */
        ~Metal() override = default;

        /**
         * Scatters the ray if it has been hit.
         * 
         * \param ray           The incoming ray.
         * \param record        The hit information of the ray.
         * \param attenuation   The added color value of the ray.
         * \param scattered     The outgoing scattered ray.
         * 
         * \return true, if the ray has been scattered.
        */
        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        glm::vec4 m_Albedo;
        f32 m_Fuzz = 0.0f;
    };

//  ==================================================
//  Dielectric
//  ==================================================

    /**
     * Defines a glass-like material.
    */
    class Dielectric final : public Material
    {
    public:
        /**
         * Constructs a new dielectric material.
         * 
         * \param refractiveIndex   The level of transparency.
        */
        Dielectric(f32 refractiveIndex);

        /**
         * Destroys the material.
        */
        ~Dielectric() override = default;

        /**
         * Scatters the ray if it has been hit.
         * 
         * \param ray           The incoming ray.
         * \param record        The hit information of the ray.
         * \param attenuation   The added color value of the ray.
         * \param scattered     The outgoing scattered ray.
         * 
         * \return true, if the ray has been scattered.
        */
        bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const override;

    private:
        /**
         * Calculates the refraction of the input vector.
         * 
         * \param v         The vector to calculate the refraction for.
         * \param n         The normal of the surface.
         * \param niOverNT  The refractive index ratio.
         * \param refracted The refracted vector.
         * 
         * \return true, if refraction is possible.
        */
        bool Refract(const glm::vec3& v, const glm::vec3& n, f32 niOverNT, glm::vec3& refracted) const;

        /**
         * Calculates the reflectance of light.
         * 
         * \param cosine Cosine of angle between the ray and surface normal.
         * 
         * \return The reflectance value.
        */
        f32 Schlick(f32 cosine) const;

    private:
        f32 m_RefractiveIndex;
    };

} // namespace rt
