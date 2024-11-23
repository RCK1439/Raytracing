#include "ArgumentParser.hpp"
#include "Timer.hpp"
#include "Renderer/Renderer.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <cstdlib>
#include <print>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    for (int32_t i = 1; i < argc; i++)
    {
        args.emplace_back(argv[i]);
    }

    const Arguments settings = ArgumentParser::Parse(args);
    if (settings.ShowHelp)
    {
        std::println("-s or -S: Size of output image.            (e.g. -s 1280 720)");
        std::println("-a or -A: Number of anti-aliasing samples. (e.g. -a 32)");
        std::println("-d or -D: Depth of ray bounces.            (e.g. -d 8)");
        std::println("-o:       Output path for rendered image.  (e.g. -o path/on/disk/name.png)");
        std::println("-help:    Shows this dialog.               (e.g. -help)");

        return EXIT_SUCCESS;
    }

    rt::Renderer::Init(settings.Width, settings.Height, settings.NumberOfSamples, settings.Depth);

    std::println("Dimensions: {}x{}", settings.Width, settings.Height);
    std::println("Anti-aliasing samples: {}", settings.NumberOfSamples);
    std::println("Maximum bounce depth: {}", settings.Depth);

    Timer timer;

    rt::Scene scene;
    rt::Camera camera(
        { 13.0f, 2.0f, 3.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        20.0f,
        static_cast<float>(settings.Width) / static_cast<float>(settings.Height),
        0.1f,
        10.0f
    );

    timer.Start();
    rt::Renderer::Render(scene, camera);
    timer.Stop();

    rt::Renderer::Export(settings.OutputPath);
}
