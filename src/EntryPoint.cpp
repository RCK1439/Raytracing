#include "Camera.hpp"
#include "Dielectric.hpp"
#include "HitableList.hpp"
#include "Image.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Random.hpp"
#include "Sphere.hpp"

#include <glm/geometric.hpp>

#define WIDTH  1024
#define HEIGHT 512

#define NUM_SAMPLES 32

using namespace rt;

static glm::vec4 Lerp(const glm::vec4& from, const glm::vec4 to, f32 t)
{
    return (1.0f - t) * from + t * to;
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

    return Lerp(white, blue, t);
}

int main()
{
    Image image(WIDTH, HEIGHT);

    HitableList world;

    Sphere sphere1({  0.0f,    0.0f, -1.0f },   0.50f, new Lambertian({ 0.1f, 0.2f, 0.5f }));
    Sphere sphere2({  0.0f, -100.5f, -1.0f }, 100.00f, new Lambertian({ 0.8f, 0.8f, 0.0f }));
    Sphere sphere3({  1.0f,    0.0f, -1.0f },   0.50f, new Metal({ 0.8f, 0.6f, 0.2f }, 0.0f));
    Sphere sphere4({ -1.0f,    0.0f, -1.0f },   0.50f, new Dielectric(1.5f));
    Sphere sphere5({ -1.0f,    0.0f, -1.0f },  -0.45f, new Dielectric(1.5f));

    world.Add(&sphere1);
    world.Add(&sphere2);
    world.Add(&sphere3);
    world.Add(&sphere4);
    world.Add(&sphere5);

    glm::vec3 lookFrom = { 3.0f, 3.0f,  2.0f };
    glm::vec3 lookAt   = { 0.0f, 0.0f, -1.0f };
    Camera camera(lookFrom, lookAt, { 0.0f, 1.0f, 0.0f }, 60.0f, (f32)WIDTH / (f32)HEIGHT, 2.0f, glm::length(lookFrom - lookAt));

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
        }
    }

    image.Save("out/test.png");

    return 0;
}