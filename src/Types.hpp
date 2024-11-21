/**
 * Ruan C. Keet (2023)
 * Types.hpp
*/

#pragma once

#include <glm/vec3.hpp>

#include <memory>

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef float               f32;
typedef double              f64;

namespace rt
{
    class Material;

    struct HitRecord
    {
        f32                       t;
        glm::vec3                 Point;
        glm::vec3                 Normal;
        std::shared_ptr<Material> Mat;
    };

    struct Ray
    {
        glm::vec3 Origin;
        glm::vec3 Direction;

        /**
         * \brief Gets the point on the ray at the specified parameter.
         * 
         * \param t The parameter to get the point at.
         * 
         * \return The point on the ray at the t-parameter.
        */
        inline glm::vec3 PointAt(f32 t) const { return Origin + t * Direction; }
    };
}
