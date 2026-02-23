#pragma once

#include "Image.hpp"

#include "Core/Types.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <glm/vec4.hpp>

#include <filesystem>
#include <vector>

namespace RTIAW {

class Renderer final
{
public:
    Renderer(u32 width, u32 height, u32 numSamples, u32 depth) noexcept;

    void Render(const Scene& scene, const Camera& camera) noexcept;
    
    inline Result<void, RendererError> Export(const std::filesystem::path& path) const noexcept { return m_Image.Save(path); }

private:
    void PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera) noexcept;
    glm::vec4 GetColor(const Ray& ray, const Scene& scene, u32 depth) const noexcept;

private:
    std::vector<u32> m_PixelIndices{};
    Image            m_Image{};
    u32              m_MaxDepth{};
    u32              m_NumSamples{};
};

}
