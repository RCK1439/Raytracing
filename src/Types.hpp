#pragma once

#include <glm/vec3.hpp>

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
        f32       t;
        glm::vec3 Point;
        glm::vec3 Normal;
        Material* Mat;
    };

    struct Ray
    {
        glm::vec3 Origin;
        glm::vec3 Direction;

        inline glm::vec3 PointAt(f32 t) const { return Origin + t * Direction; }
    };
} // namespace rt
