/**
 * Ruan C. Keet (2023)
 * Random.hpp
*/

#pragma once

#include "Types.hpp"

namespace rt
{
    /**
     * Class to generate random values.
    */
    class Random
    {
    public:
        /**
         * Initializes the random number generator.
        */
        static void Init();

        /**
         * Gets a random float between 0 and 1.
         * 
         * \return A random floating point value.
        */
        static f32 Float();

        /**
         * Gets a random point inside a unit sphere.
         * 
         * \return A random position inside a unit sphere.
        */
        static glm::vec3 InUnitSphere();

        /**
         * Gets a random point on a unit disk.
         * 
         * \return A random point on a unit disk.
        */
        static glm::vec3 InUnitDisk();
    };
} // namespace rt
