#include "Scene.hpp"
#include "Random.hpp"
#include "Materials/Materials.hpp"

namespace rt
{
    constexpr float RADIUS = 0.2f;

    inline static Sphere CreateMatteSphere(const glm::vec3& position)
    {
        return Sphere(position, RADIUS, new Lambertian(
        { 
            Random::Float() * Random::Float(),
            Random::Float() * Random::Float(), 
            Random::Float() * Random::Float() 
        }));
    }

    inline static Sphere CreateMetalSphere(const glm::vec3& position)
    {
        return Sphere(position, 0.2f, new Metal(
        { 
            0.5f * (1.0f + Random::Float()), 
            0.5f * (1.0f + Random::Float()), 
            0.5f * (1.0f + Random::Float()) 
        },  0.5f * (1.0f + Random::Float())));
    }

    inline static Sphere CreateDielectricSphere(const glm::vec3& position)
    {
        return Sphere(position, 0.2f, new Dielectric(1.5f));
    }

    Scene::Scene() // This makes the default cover-page scene.
    {
        Add(Sphere({ 0.0f, -1000.0f, 0.0f }, 1000.0f, new Lambertian({ 0.5f, 0.5f, 0.5f })));
        for (int32_t a = -11; a < 11; a++)
        {
            for (int32_t b = -11; b < 11; b++)
            {
                const float chooseMaterial = Random::Float();
                const glm::vec3 center = { a + 0.9f * Random::Float(), 0.2f, b + 0.9f * Random::Float() };

                if (chooseMaterial < 0.80f)
                {
                    m_Objects.emplace_back(CreateMatteSphere(center));
                }
                else if (chooseMaterial < 0.95f)
                {
                    m_Objects.emplace_back(CreateMetalSphere(center));
                }
                else
                {
                    m_Objects.emplace_back(CreateDielectricSphere(center));
                }
            }
        }

        Add(Sphere({  0.0f, 1.0f, 0.0f }, 1.0f, new Dielectric(1.5f)));
        Add(Sphere({ -4.0f, 1.0f, 0.0f},  1.0f, new Lambertian({ 0.4f, 0.2f, 0.1f })));
        Add(Sphere({  4.0f, 1.0f, 0.0f},  1.0f, new Metal({ 0.7f, 0.6f, 0.5f }, 0.0f)));
    }

    bool Scene::Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
    {
        HitRecord tempRecord;

        bool hitAnything = false;
        float closest = tMax;
        for (const auto& obj : m_Objects)
        {
            if (obj.Hit(ray, tMin, closest, tempRecord))
            {
                hitAnything = true;
                closest = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAnything;
    }

    void Scene::Add(Sphere&& obj)
    {
        m_Objects.emplace_back(obj);
    }
}
