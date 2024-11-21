#pragma once

#include "Types.hpp"

namespace rt
{ 
    class Camera
    {
    public: 
        Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, f32 vFOV, f32 aspectRatio, f32 aperture, f32 focusDistance); 

        Ray GetRay(f32 s, f32 t) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_LowerLeftCorner;
        glm::vec3 m_Horizontal;
        glm::vec3 m_Vertical;
        glm::vec3 u, v, w;
        f32       m_LensRadius;
    };
}
