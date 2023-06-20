/**
 * Ruan C. Keet (2023)
 * Material.hpp
*/

#pragma once

#include "Types.hpp"

#include <glm/vec4.hpp>

namespace rt
{
    struct HitRecord;
    
    /**
     * This class defines the API to be used by different materials.
    */
    class Material
    {
    public:
        /**
         * Default destructor for the material.
        */
        virtual ~Material() = default;

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
        virtual bool Scatter(const Ray& ray, const HitRecord& record, glm::vec4& attenuation, Ray& scattered) const = 0;
    };
} // namespace rt
