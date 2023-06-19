#include "Camera.hpp"
#include "Random.hpp"

#include <glm/geometric.hpp>
#include <math.h>

namespace rt
{
    Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, f32 vFOV, f32 aspectRatio, f32 aperture, f32 focusDistance) :
        m_Origin(lookFrom), m_LensRadius(aperture * 0.5f)
    {
        const f32 theta      = vFOV * M_PI / 180.0f;
        const f32 halfHeight = tanf(theta * 0.5f);
        const f32 halfWidth  = aspectRatio * halfHeight;

        w = glm::normalize(lookFrom - lookAt);
        u = glm::normalize(glm::cross(vUP, w));
        v = glm::cross(w, u);

        m_LowerLeftCorner = m_Origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
        m_Horizontal      = 2.0f * halfWidth * focusDistance * u;
        m_Vertical        = 2.0f * halfHeight * focusDistance * v;
    }

    Ray Camera::GetRay(f32 s, f32 t) const
    {
        glm::vec3 rd = m_LensRadius * Random::InUnitDisk();
        glm::vec3 offset = u * rd.x + v * rd.y;

        return { m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset };
    }

} // namespace rt
