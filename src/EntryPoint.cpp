#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <string>

using namespace rt;

int main(int argc, char* argv[])
{
    const u32 width      = 1024;
    const u32 height     = 512;
    const u32 numSamples = 32;
    const u32 depth      = 50;

    std::cout << "Dimensions: " << width << "x" << height << std::endl;
    std::cout << "Anti-aliasing samples: " << numSamples << std::endl;
    std::cout << "Maximum bounce depth: " << depth << std::endl;

    std::string output = "out/rt.png";



    Renderer::Init(width, height, numSamples, depth);

    Scene scene;

    glm::vec3 lookFrom = { 13.0f, 2.0f, 3.0f };
    glm::vec3 lookAt   = {  0.0f, 0.0f, 0.0f };
    Camera camera(lookFrom, lookAt, { 0.0f, 1.0f, 0.0f }, 20.0f, (f32)width / (f32)height, 0.1f, 10.0f);

    Renderer::Render(scene, camera);
    Renderer::Export(output);

    return 0;
}