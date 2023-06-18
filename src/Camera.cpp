#include "Camera.hpp"

namespace rt
{
    Camera::Camera() :
        m_Origin(0.0f), m_LowerLeftCorner(-2.0f, -1.0f, -1.0f), m_Horizontal(4.0f, 0.0f, 0.0f), m_Vertical(0.0f, 2.0f, 0.0f)
    {
    }
} // namespace rt
