#include "Camera.hpp"
#include "HitableList.hpp"
#include "Image.hpp"
#include "Random.hpp"
#include "Sphere.hpp"

#include <glm/geometric.hpp>

#define WIDTH  512
#define HEIGHT 256

#define NUM_SAMPLES 50

using namespace rt;

static glm::vec4 Lerp(const glm::vec4& from, const glm::vec4 to, f32 t)
{
    return (1.0f - t) * from + t * to;
}

static glm::vec4 GetColor(const Ray& ray, const Hitable& world)
{
    HitRecord record;

    if (world.Hit(ray, 0.0f, __FLT_MAX__, record))
    {
        glm::vec4 color = { record.Normal.x + 1.0f, record.Normal.y + 1.0f, record.Normal.z + 1.0f, 2.0f /*This is for the multiply in the next line*/ };
        return 0.5f * color;
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

    Sphere sphere1(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    Sphere sphere2(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f);

    world.Add(&sphere1);
    world.Add(&sphere2);

    Camera camera;

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

                color += GetColor(ray, world);
            }
            color /= (f32)NUM_SAMPLES;
            image.SetColor(x, y, color); 
        }
    }

    image.Save("out/test.png");

    return 0;
}