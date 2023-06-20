#pragma once

#include "Camera.hpp"
#include "Types.hpp"
#include "Scene.hpp"

#include <glm/vec4.hpp>

#include <string_view>

namespace rt
{
    class Renderer
    {
    public:
        static void Init(u32 width, u32 height, u32 numSamples, u32 depth);
        static void Export(std::string_view filepath);

        static void Render(const Scene& scene, const Camera& camera);

    private:
        static void PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera);
        static glm::vec4 GetColor(const Ray& ray, const Scene& scene, u32 depth);

        static void ShowProgressBar();
    };
} // namespace rt
