/**
 * Ruan C. Keet (2023)
 * Renderer.cpp
*/

#include "Renderer.hpp"

#include "Image.hpp"
#include "Materials.hpp"
#include "Random.hpp"

#include <glm/geometric.hpp>

#include <omp.h>
#include <iostream>
#include <iomanip>

namespace rt
{
    struct RendererData
    {
        Image Img;
        u32   MaxDepth;
        u32   CurrentPixel;
        u32   TotalPixels;
        u32   NumSamples;
    };

    static RendererData s_Data;

    void Renderer::Init(u32 width, u32 height, u32 numSamples, u32 depth)
    {
        s_Data.Img.Resize(width, height);
        
        s_Data.MaxDepth     = depth;
        s_Data.CurrentPixel = 0;
        s_Data.TotalPixels  = width * height;
        s_Data.NumSamples   = numSamples;
    }

    void Renderer::Export(std::string_view filepath)
    {
        s_Data.Img.Save(filepath);
    }

    void Renderer::Render(const Scene& scene, const Camera& camera)
    {
        const u32 width  = s_Data.Img.GetWidth();
        const u32 height = s_Data.Img.GetHeight();

        #pragma omp parallel for collapse(2)
        for (u32 y = 0; y < height; y++)
        {
            for (u32 x = 0; x < width; x++)
            {
                PerPixel(x, y, scene, camera);

                #pragma omp critical
                {
                    ++s_Data.CurrentPixel;
                    ShowProgressBar();
                }
            }
        }

        std::cout << std::endl; // This is for the progress bar.
    }

    void Renderer::PerPixel(u32 x, u32 y, const Scene& scene, const Camera& camera)
    {
        glm::vec4 color(0.0f);

        for (u32 s = 0; s < s_Data.NumSamples; s++)
        {
            f32 u = f32(x + Random::Float()) / (f32)s_Data.Img.GetWidth();
            f32 v = f32(y + Random::Float()) / (f32)s_Data.Img.GetHeight();

            Ray ray = camera.GetRay(u, v);

            color += GetColor(ray, scene, 0);
        }

        color /= (f32)s_Data.NumSamples;
        glm::vec4 gammaCorrected = { sqrtf(color.r), sqrtf(color.g), sqrtf(color.b), 1.0f };

        s_Data.Img.SetColor(x, y, gammaCorrected); 
    }

    glm::vec4 Renderer::GetColor(const Ray& ray, const Scene& scene, u32 depth)
    {   
        constexpr glm::vec4 BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
        constexpr glm::vec4 BLUE  = { 0.5f, 0.7f, 1.0f, 1.0f };
        constexpr glm::vec4 WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

        HitRecord record;

        if (scene.Hit(ray, 0.0001f, std::numeric_limits<f32>::max(), record))
        {
            Ray scattered;
            glm::vec4 attenuation;

            return depth < s_Data.MaxDepth && record.Mat->Scatter(ray, record, attenuation, scattered) ? attenuation * GetColor(scattered, scene, depth + 1) : BLACK;
        }

        f32 t = 0.5f * ray.Direction.y + 1.0f;

        return glm::mix(WHITE, BLUE, t);    // This gives us the sky colour.
    }

    void Renderer::ShowProgressBar()
    {
        constexpr u32 BAR_WIDTH = 50;

        const f32 progress = (f32)s_Data.CurrentPixel / (f32)s_Data.TotalPixels;
        const u32 pos = BAR_WIDTH * progress;

        std::cout << "Renderering: [";
        for (u32 i = 0; i < BAR_WIDTH; i++) 
        {
            char bar;

            if      (i < pos)  bar = '=';
            else if (i == pos) bar = '>';
            else               bar = ' ';

            std::cout << bar;
        }

        std::cout << "] " << std::setw(3) << u32(progress * 100.0f) << "%\r";
        std::cout.flush();
    }
} // namespace rt
