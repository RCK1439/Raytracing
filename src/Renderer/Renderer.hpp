#pragma once

#include "Image.hpp"

#include "Core/Types.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <glm/vec4.hpp>

#include <filesystem>

namespace RTIAW {

class Renderer final
{
public:
    Renderer(u32 width, u32 height, u32 numSamples, u32 depth);

    void Render(const Scene& scene, const Camera& camera);
    
    inline Result<void, RendererError> Export(const std::filesystem::path& path) const { return m_Image.Save(path); }

private:
    void PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera);
    glm::vec4 GetColor(const Ray& ray, const Scene& scene, u32 depth) const;

private:
    Image m_Image{};
    u32   m_MaxDepth{};
    u32   m_NumSamples{};
};

}
