#include "Camera.hpp"

#include <glm/geometric.hpp>
#include <math.h>

namespace rt
{
    Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, f32 vFOV, f32 aspectRatio) :
        m_Origin(lookFrom)
    {
        const f32 theta      = vFOV * M_PI / 180.0f;
        const f32 halfHeight = tanf(theta * 0.5f);
        const f32 halfWidth  = aspectRatio * halfHeight;

        glm::vec3 w = glm::normalize(lookFrom - lookAt);
        glm::vec3 u = glm::normalize(glm::cross(vUP, w));
        glm::vec3 v = glm::cross(w, u);

        m_LowerLeftCorner = m_Origin - halfWidth * u - halfHeight * v - w;
        m_Horizontal      = 2.0f * halfWidth * u;
        m_Vertical        = 2.0f * halfHeight * v;
    }
} // namespace rt
