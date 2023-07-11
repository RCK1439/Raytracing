/**
 * Ruan C. Keet (2023)
 * Camera.hpp
*/

#pragma once

#include "Types.hpp"

namespace rt
{
    /**
     * \brief Class representing the camera looking into our scene.
    */
    class Camera
    {
    public:
        /**
         * \brief Constructs a new camera.
         * 
         * \param lookFrom      The position of the camera
         * \param lookAt        The position the camera is looking at.
         * \param vUP           The direction which is vertically upwards.
         * \param vFOV          The vertical field of view.
         * \param aspectRatio   The aspect ratio of the image.
         * \param aperture      The radial focus of the camera lens.
         * \param focusDistance The distance at which all objects remain in focus.
        */
        Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUP, f32 vFOV, f32 aspectRatio, f32 aperture, f32 focusDistance);

        /**
         * \brief Destroys the camera
        */
        ~Camera() = default;

        /**
         * \brief Gets the ray at the specified pixel-coordinates.
         * 
         * \param s The x-coordinate of the pixel.
         * \param t The y-coordinate of the pixel.
         * 
         * \return The ray coming from that pixel.
        */
        Ray GetRay(f32 s, f32 t) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_LowerLeftCorner;
        glm::vec3 m_Horizontal;
        glm::vec3 m_Vertical;
        glm::vec3 u, v, w;
        f32 m_LensRadius;
    };
} // namespace rt
