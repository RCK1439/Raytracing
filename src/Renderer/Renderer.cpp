#include "Renderer.hpp"
#include "Image.hpp"
#include "Random.hpp"
#include "Scene/Materials/Material.hpp"
#include "Scene/Materials/HitRecord.hpp"

#include <glm/geometric.hpp>
#include <omp.h>

#include <iostream>
#include <iomanip>

namespace rt
{
    struct RendererData
    {
        Image    Img;
        uint32_t MaxDepth;
        uint32_t CurrentPixel;
        uint32_t TotalPixels;
        uint32_t NumSamples;
    };

    static RendererData s_Data;

    void Renderer::Init(uint32_t width, uint32_t height, uint32_t numSamples, uint32_t depth)
    {
        s_Data.Img.Resize(width, height);
        
        s_Data.MaxDepth     = depth;
        s_Data.CurrentPixel = 0;
        s_Data.TotalPixels  = width * height;
        s_Data.NumSamples   = numSamples;
    }

    std::expected<void, RendererError> Renderer::Export(std::string_view filepath)
    {
        return s_Data.Img.Save(filepath);
    }

    void Renderer::Render(const Scene& scene, const Camera& camera)
    {
        const uint32_t width = s_Data.Img.GetWidth();

        #pragma omp parallel for
        for (uint32_t p = 0; p < s_Data.TotalPixels; p++)
        {
            const uint32_t x = p % width;
            const uint32_t y = p / width;
            PerPixel(x, y, scene, camera);
            
            #pragma omp critical
            {
                ++s_Data.CurrentPixel;
                ShowProgressBar();
            }
        }

        std::cout << std::endl; // This is for the progress bar.
    }

    void Renderer::PerPixel(uint32_t x, uint32_t y, const Scene& scene, const Camera& camera)
    {
        glm::vec4 color(0.0f);

        for (uint32_t s = 0; s < s_Data.NumSamples; s++)
        {
            const float u = static_cast<float>(x + Random::Float()) / static_cast<float>(s_Data.Img.GetWidth());
            const float v = static_cast<float>(y + Random::Float()) / static_cast<float>(s_Data.Img.GetHeight());

            const Ray ray = camera.GetRay(u, v);

            color += GetColor(ray, scene, 0);
        }

        color /= static_cast<float>(s_Data.NumSamples);
        const glm::vec4 gammaCorrected = { sqrtf(color.r), sqrtf(color.g), sqrtf(color.b), 1.0f };

        s_Data.Img.SetColor(x, y, gammaCorrected); 
    }

    glm::vec4 Renderer::GetColor(const Ray& ray, const Scene& scene, uint32_t depth)
    {   
        constexpr glm::vec4 BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
        constexpr glm::vec4 BLUE  = { 0.5f, 0.7f, 1.0f, 1.0f };
        constexpr glm::vec4 WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

        HitRecord record;

        if (scene.Hit(ray, 0.0001f, std::numeric_limits<float>::max(), record))
        {
            Ray scattered;
            glm::vec4 attenuation;

            return depth < s_Data.MaxDepth && record.Mat->Scatter(ray, record, attenuation, scattered) ? attenuation * GetColor(scattered, scene, depth + 1) : BLACK;
        }

        const float t = 0.5f * ray.Direction.y + 1.0f;

        return glm::mix(WHITE, BLUE, t);    // This gives us the sky colour.
    }

    void Renderer::ShowProgressBar()
    {
        constexpr uint32_t BAR_WIDTH = 50;

        const float progress = static_cast<float>(s_Data.CurrentPixel) / static_cast<float>(s_Data.TotalPixels);
        const uint32_t pos = BAR_WIDTH * progress;

        std::cout << "Renderering: [";
        for (uint32_t i = 0; i < BAR_WIDTH; i++) 
        {
            std::cout << (i < pos ? '#' : '.');
        }

        std::cout << "] " << std::setw(3) << static_cast<uint32_t>(progress * 100.0f) << "%\r";
        std::cout.flush();
    }
}
