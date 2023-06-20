/**
 * Ruan C. Keet (2023)
 * Renderer.hpp
*/

#pragma once

#include "Camera.hpp"
#include "Types.hpp"
#include "Scene.hpp"

#include <glm/vec4.hpp>

#include <string_view>

namespace rt
{
    /**
     * Class handling all the rendering of ray tracing
     * algorithm.
    */
    class Renderer
    {
    public:
        /**
         * Initializes the renderer.
         * 
         * \param width         The width of the viewport.
         * \param height        The height of the viewport.
         * \param numSamples    The number of samples for anti-aliasing.
         * \param depth         The maximum amount of ray bounces.
        */
        static void Init(u32 width, u32 height, u32 numSamples, u32 depth);

        /**
         * Expores the rendered image to the output path.
         * 
         * \param filepath  The directory to save the image to.
        */
        static void Export(std::string_view filepath);

        /**
         * Renders the given scene to an image,
         * 
         * \param scene     The scene to render.
         * \param camera    The camera defining the view into the scene.
        */
        static void Render(const Scene& scene, const Camera& camera);

    private:
        /**
         * The code to run for every pixel on the image.
         * 
         * \param x         The x-coordinate of the pixel.
         * \param y         The y-coordinate of the pixel.
         * \param scene     The scene to render.
         * \param camera    The camera defining the view into the scene.
        */
        static void PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera);

        /**
         * Gets the final color of the ray.
         * 
         * \param ray   The ray sent out into the scene.
         * \param scene The scene to render.
         * \param depth The maximum amount of ray bounces.
        */
        static glm::vec4 GetColor(const Ray& ray, const Scene& scene, u32 depth);

        /**
         * Shows and updates the progress bar on the terminal.
        */
        static void ShowProgressBar();
    };
} // namespace rt
