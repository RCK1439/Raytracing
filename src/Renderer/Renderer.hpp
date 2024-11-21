#pragma once

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <glm/vec4.hpp>

#include <string_view>

namespace rt
{
    class Renderer
    {
    public:
        static void Init(uint32_t width, uint32_t height, uint32_t numSamples, uint32_t depth);

        static void Export(std::string_view filepath);

        static void Render(const Scene& scene, const Camera& camera);

    private:
        static void PerPixel(uint32_t x, uint32_t y, const Scene& scene, const Camera& camera);
        static glm::vec4 GetColor(const Ray& ray, const Scene& scene, uint32_t depth);
        static void ShowProgressBar();
    };
}
