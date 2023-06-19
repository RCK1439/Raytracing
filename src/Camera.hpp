#pragma once

#include "Types.hpp"

namespace rt
{
    class Camera
    {
    public:
        Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, f32 vFOV, f32 aspectRatio);
        ~Camera() = default;

        inline Ray GetRay(f32 u, f32 v) const { return { m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin }; }

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_LowerLeftCorner;
        glm::vec3 m_Horizontal;
        glm::vec3 m_Vertical;
    };
} // namespace rt
