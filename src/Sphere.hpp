/**
 * Ruan C. Keet (2023)
 * Sphere.hpp
*/

#pragma once

#include "Types.hpp"

#include <memory>

namespace rt
{
    /**
     * This class defines a sphere object.
    */
    class Sphere
    {
    public:
        /**
         * Constructs a new sphere.
        */
        Sphere() = default;

        /**
         * Constructs a new sphere with parameters.
         * 
         * \param position  The position of the center of the sphere.
         * \param radius    The radius of the sphere.
         * \param material  The material to give the sphere.
        */
        Sphere(const glm::vec3& position, f32 radius, Material* material);

        /**
         * Destroys the sphere.
        */
        ~Sphere() = default;

        /**
         * Checks if the incoming ray hits the sphere.
         * 
         * \param ray       The incoming ray.
         * \param tMin      The near plane.
         * \param tMax      The far plane.
         * \param record    The record to save the hit information to.
         * 
         * \return true, if the ray hits the sphere.
        */
        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

    private:
        /**
         * Checks if the root falls between the planes.
         * 
         * \param ray       The incoming ray.
         * \param tMin      The near plane.
         * \param tMax      The far plane.
         * \param temp      The root to check for.
         * \param record    The record where the hit information will be saved to.
         * 
         * \return true, if the root falls between tMin and tMax.
        */
        bool CheckRoot(const Ray& ray, f32 tMin, f32 tMax, f32 temp, HitRecord& record) const;

    private:
        glm::vec3 m_Centre;
        f32 m_Radius;
        std::shared_ptr<Material> m_Material = nullptr;
    };
} // namespace rt
