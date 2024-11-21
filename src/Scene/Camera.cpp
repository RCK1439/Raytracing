#include "Camera.hpp"
#include "Random.hpp"

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

namespace rt
{
    Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, float vFOV, float aspectRatio, float aperture, float focusDistance) :
        m_Origin(lookFrom), m_LensRadius(aperture * 0.5f)
    {
        const float theta = vFOV * glm::pi<float>() / 180.0f;
        const float halfHeight = glm::tan(theta * 0.5f);
        const float halfWidth = aspectRatio * halfHeight;

        w = glm::normalize(lookFrom - lookAt);
        u = glm::normalize(glm::cross(vUP, w));
        v = glm::cross(w, u);

        m_LowerLeftCorner = m_Origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
        m_Horizontal = 2.0f * halfWidth * focusDistance * u;
        m_Vertical = 2.0f * halfHeight * focusDistance * v;
    }

    Ray Camera::GetRay(float s, float t) const
    {
        const glm::vec3 rd = m_LensRadius * Random::InUnitDisk();
        const glm::vec3 offset = u * rd.x + v * rd.y;

        const glm::vec3 origin = m_Origin + offset;
        const glm::vec3 direction = glm::normalize(m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset);

        return { origin, direction };
    }

}
