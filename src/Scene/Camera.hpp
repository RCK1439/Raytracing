#pragma once

#include "Renderer/Ray.hpp"

namespace rt
{ 
    class Camera
    {
    public: 
        Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, float vFOV, float aspectRatio, float aperture, float focusDistance); 

        Ray GetRay(float s, float t) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_LowerLeftCorner;
        glm::vec3 m_Horizontal;
        glm::vec3 m_Vertical;
        glm::vec3 u, v, w;
        float     m_LensRadius;
    };
}
