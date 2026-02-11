#pragma once

#include "Types.hpp"

#include "Error.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <glm/vec4.hpp>

#include <filesystem>

namespace rt {

class Renderer final
{
public:
    static void Init(u32 width, u32 height, u32 numSamples, u32 depth);

    static Result<void, RendererError> Export(std::filesystem::path outputPath);

    static void Render(const Scene& scene, const Camera& camera);

private:
    static void PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera);
    static glm::vec4 GetColor(const Ray& ray, const Scene& scene, u32 depth);
};

}
