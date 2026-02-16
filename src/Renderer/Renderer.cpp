#include "Renderer.hpp"
#include "Image.hpp"

#include "Core/Random.hpp"

#include "Scene/Materials/Material.hpp"
#include "Scene/Materials/HitRecord.hpp"

#include <glm/geometric.hpp>

#include <algorithm>
#include <execution>
#include <numeric>

namespace RTIAW {

void Renderer::Render(const Scene& scene, const Camera& camera)
{
    const u32 width = m_Image.GetWidth();
    const u32 height = m_Image.GetHeight();
    const u32 totalPixels = width * height;

    std::vector<u32> pixels(totalPixels);
    std::iota(pixels.begin(), pixels.end(), 0);
    std::for_each(std::execution::par, pixels.begin(), pixels.end(),
        [&](u32 p)
        {
            const u32 x = p % width;
            const u32 y = p / width;
            PerPixel(x, y, scene, camera);
        });
}

void Renderer::PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera)
{
    glm::vec4 color(0.0f);

    for (u32 s{}; s < m_NumSamples; s++)
    {
        const f32 u = static_cast<f32>(x + Random::Float()) / static_cast<f32>(m_Image.GetWidth());
        const f32 v = static_cast<f32>(y + Random::Float()) / static_cast<f32>(m_Image.GetHeight());

        const Ray ray = camera.GetRay(u, v);

        color += GetColor(ray, scene, 0);
    }

    color /= static_cast<f32>(m_NumSamples);
    const glm::vec4 gammaCorrected = glm::sqrt(color);

    m_Image.SetColor(x, y, gammaCorrected); 
}

glm::vec4 Renderer::GetColor(const Ray& ray, const Scene& scene, u32 depth) const
{
    constexpr glm::vec4 BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
    constexpr glm::vec4 BLUE  = { 0.5f, 0.7f, 1.0f, 1.0f };
    constexpr glm::vec4 WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

    if (depth >= m_MaxDepth)
        return BLACK;

    if (const auto hit = scene.Hit(ray, 0.0001f, std::numeric_limits<f32>::max()))
    {
        const HitRecord record = hit.value();
        if (const auto data = record.Mat->Scatter(ray, record))
            return data->Attenuation * GetColor(data->Scattered, scene, depth + 1);
    }

    const f32 t = 0.5f * ray.Direction.y + 1.0f;
    return glm::mix(WHITE, BLUE, t);    // This gives us the sky colour.
}

}
