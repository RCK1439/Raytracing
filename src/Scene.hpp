/**
 * Ruan C. Keet (2023)
 * Scene.hpp
*/

#pragma once

#include "Sphere.hpp"

#include <vector>

namespace rt
{
    /**
     * \brief Class to define our scene.
     * 
     * Holds all the objects in our scene.
    */
    class Scene
    {
    public:
        /**
         * \brief Constructs a new scene.
         * 
         * The scene constructed is the one on the cover.
        */
        Scene();

        /**
         * \brief Destroys the scene.
        */
        ~Scene() = default;

        /**
         * \brief Checks if the incoming ray has hit anything in the scene and saves
         * the hit information into the record.
         * 
         * \param ray       The incoming ray.
         * \param tMin      The near plane.
         * \param tMax      The far plane.
         * \param record    The record to save the hit information to.
         * 
         * \return true, if any object has been hit in the scene.
        */
        bool Hit(const Ray& ray, f32 tMin, f32 tMax, HitRecord& record) const;

        /**
         * \brief Adds a sphere to the scene.
         * 
         * \param obj   The sphere to add to the scene.
        */
        void Add(const Sphere& obj);
    private:
        std::vector<Sphere> m_Objects;
    };
} // namespace rt
