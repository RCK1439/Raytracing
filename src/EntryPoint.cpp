#include "Camera.hpp"
#include "HitableList.hpp"
#include "Image.hpp"
#include "Materials.hpp"
#include "Random.hpp"
#include "Sphere.hpp"

#include <glm/geometric.hpp>
#include <iostream>
#include <iomanip>
#include <stdio.h>

#define WIDTH  1024
#define HEIGHT 512

#define NUM_SAMPLES 32

using namespace rt;

static void ShowProgressBar(f32 progress)
{
    u32 barWidth = 70;

    std::cout << "Renderering: [";
    u32 pos = barWidth * progress;
    for (u32 i = 0; i < barWidth; i++) 
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

static glm::vec4 GetColor(const Ray& ray, const Hitable& world, u32 depth)
{
    HitRecord record;

    if (world.Hit(ray, 0.0001f, __FLT_MAX__, record))
    {
        Ray scattered;
        glm::vec4 attenuation;

        return depth < 50 && record.Mat->Scatter(ray, record, attenuation, scattered) ? attenuation * GetColor(scattered, world, depth + 1) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
        
    glm::vec3 unitDir = glm::normalize(ray.Direction);
    f32 t = 0.5f * unitDir.y + 1.0f;

    glm::vec4 white = glm::vec4(1.0f);
    glm::vec4 blue  = { 0.5f, 0.7f, 1.0f, 1.0f };

    return glm::mix(white, blue, t);
}

static void InitRandomWorld(HitableList& world)
{
    world.Add(Sphere({ 0.0f, -1000.0f, 0.0f }, 1000.0f, new Lambertian({ 0.5f, 0.5f, 0.5f })));
    for (s32 a = -11; a < 11; a++)
    {
        for (s32 b = -11; b < 11; b++)
        {
            f32 chooseMaterial = Random::Float();
            glm::vec3 center = { a + 0.9f * Random::Float(), 0.2f, b + 0.9f * Random::Float() };

            if (chooseMaterial < 0.8f)
            {
                world.Add(Sphere(center, 0.2f, new Lambertian(
                    { 
                        Random::Float() * Random::Float(),
                        Random::Float() * Random::Float(),
                        Random::Float() * Random::Float(),
                    })));
            }
            else if (chooseMaterial < 0.95f)
            {
                world.Add(Sphere(center, 0.2f, new Metal(
                    {
                        0.5f * (1.0f + Random::Float()),
                        0.5f * (1.0f + Random::Float()),
                        0.5f * (1.0f + Random::Float()),
                    }, 0.5f * (1.0f + Random::Float()))));
            }
            else
            {
                world.Add(Sphere(center, 0.2f, new Dielectric(1.5f)));
            }
        }
    }

    world.Add(Sphere({  0.0f, 1.0f, 0.0f }, 1.0f, new Dielectric(1.5f)));
    world.Add(Sphere({ -4.0f, 1.0f, 0.0f},  1.0f, new Lambertian({ 0.4f, 0.2f, 0.1f })));
    world.Add(Sphere({  4.0f, 1.0f, 0.0f},  1.0f, new Metal({ 0.7f, 0.6f, 0.5f }, 0.0f)));
}

int main()
{
    HitableList world;

    InitRandomWorld(world);

    glm::vec3 lookFrom = { 13.0f, 2.0f, 3.0f };
    glm::vec3 lookAt   = {  0.0f, 0.0f, 0.0f };
    Camera camera(lookFrom, lookAt, { 0.0f, 1.0f, 0.0f }, 20.0f, (f32)WIDTH / (f32)HEIGHT, 0.1f, 10.0f);

    Image image(WIDTH, HEIGHT);

    u32 current = 0;
    u32 total = WIDTH * HEIGHT;

    for (u32 y = 0; y < HEIGHT; y++)
    {
        for (u32 x = 0; x < WIDTH; x++)
        {
            glm::vec4 color(0.0f);
            for (u32 s = 0; s < NUM_SAMPLES; s++)
            {
                f32 u = f32(x + Random::Float()) / (f32)WIDTH;
                f32 v = f32(y + Random::Float()) / (f32)HEIGHT;

                Ray ray = camera.GetRay(u, v);

                color += GetColor(ray, world, 0);
            }
            color /= (f32)NUM_SAMPLES;

            glm::vec4 gammaCorrected = { sqrtf(color.r), sqrtf(color.g), sqrtf(color.b), 1.0f };

            image.SetColor(x, y, gammaCorrected); 

            ShowProgressBar(f32(++current) / (f32)total);
        }
    }
    printf("\n");

    image.Save("out/test.png");

    return 0;
}