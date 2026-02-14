#include "Scene.hpp"
#include "Random.hpp"

#include "Materials/Dielectric.hpp"
#include "Materials/Lambertian.hpp"
#include "Materials/Metal.hpp"
#include "Materials/HitRecord.hpp"

namespace rt {

constexpr f32 RADIUS = 0.2f;

static Sphere CreateMatteSphere(const glm::vec3& position)
{
    const glm::vec3 albedo = 
    {
        Random::Float() * Random::Float(),
        Random::Float() * Random::Float(),
        Random::Float() * Random::Float()
    };
    const Ref<Lambertian> material = CreateRef<Lambertian>(albedo);

    return Sphere(position, RADIUS, material);
}

static Sphere CreateMetalSphere(const glm::vec3& position)
{
    const glm::vec3 albedo =
    { 
        0.5f * (1.0f + Random::Float()), 
        0.5f * (1.0f + Random::Float()), 
        0.5f * (1.0f + Random::Float()) 
    };
    const f32 fuzz = 0.5f * (1.0f * Random::Float());
    const Ref<Metal> material = CreateRef<Metal>(albedo, fuzz);
    
    return Sphere(position, RADIUS, material);
}

static Sphere CreateDielectricSphere(const glm::vec3& position)
{
    constexpr f32 REFRACTIVE_INDEX = 1.5f;
    const Ref<Dielectric> material = CreateRef<Dielectric>(REFRACTIVE_INDEX);

    return Sphere(position, RADIUS, material);
}

Scene::Scene() // This makes the default cover-page scene.
{
    Add(glm::vec3{ 0.0f, -1000.0f, 0.0f }, 1000.0f, CreateRef<Lambertian>(glm::vec3{ 0.5f, 0.5f, 0.5f }));
    for (i32 a = -11; a < 11; a++)
    {
        for (i32 b = -11; b < 11; b++)
        {
            const f32 chooseMaterial = Random::Float();
            const glm::vec3 center = { a + 0.9f * Random::Float(), 0.2f, b + 0.9f * Random::Float() };

            if (chooseMaterial < 0.8f)
                Add(CreateMatteSphere(center));
            else if (chooseMaterial < 0.95f)
                Add(CreateMetalSphere(center));
            else
                Add(CreateDielectricSphere(center));
        }
    }

    Add(glm::vec3{  0.0f, 1.0f, 0.0f }, 1.0f, CreateRef<Dielectric>(1.5f));
    Add(glm::vec3{ -4.0f, 1.0f, 0.0f},  1.0f, CreateRef<Lambertian>(glm::vec3{ 0.4f, 0.2f, 0.1f }));
    Add(glm::vec3{  4.0f, 1.0f, 0.0f},  1.0f, CreateRef<Metal>(glm::vec3{ 0.7f, 0.6f, 0.5f }, 0.0f));
}

Option<HitRecord> Scene::Hit(const Ray& ray, f32 tMin, f32 tMax) const
{
    Option<HitRecord> finalHit{};

    f32 closest = tMax;
    for (const auto& obj : m_Objects)
    {
        if (const auto hit = obj.Hit(ray, tMin, closest))
        {
            closest = hit->t;
            finalHit = hit.value();
        }
    }

    return finalHit;
}

}
