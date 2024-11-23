#include "Config.hpp"
#include "Timer.hpp"
#include "Renderer/Renderer.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

#include <cstdlib>
#include <expected>
#include <print>

int32_t main(int32_t argc, char* argv[])
{
    const auto parsed = Config::FromArgs(argc, argv);
    if (!parsed.has_value())
    {
        const ConfigError err = parsed.error();
        std::println("{}", err.What());

        return EXIT_FAILURE;
    }

    const Config cfg = parsed.value();
    if (cfg.ShowHelp)
    {
        std::println("-s or -S: Size of output image.            (e.g. -s 1280 720)");
        std::println("-a or -A: Number of anti-aliasing samples. (e.g. -a 32)");
        std::println("-d or -D: Depth of ray bounces.            (e.g. -d 8)");
        std::println("-o:       Output path for rendered image.  (e.g. -o path/on/disk/name.png)");
        std::println("-help:    Shows this dialog.               (e.g. -help)");

        return EXIT_SUCCESS;
    }

    rt::Renderer::Init(cfg.Width, cfg.Height, cfg.NumberOfSamples, cfg.Depth);

    std::println("Dimensions: {}x{}", cfg.Width, cfg.Height);
    std::println("Anti-aliasing samples: {}", cfg.NumberOfSamples);
    std::println("Maximum bounce depth: {}", cfg.Depth);

    Timer timer;

    rt::Scene scene;
    rt::Camera camera(
        { 13.0f, 2.0f, 3.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        20.0f,
        static_cast<float>(cfg.Width) / static_cast<float>(cfg.Height),
        0.1f,
        10.0f
    );

    timer.Start();
    rt::Renderer::Render(scene, camera);
    timer.Stop();

    const auto result = rt::Renderer::Export(cfg.OutputPath);
    if (!result)
    {
        const rt::RendererError err = result.error();
        
        std::println("{}", err.What());
        return EXIT_FAILURE;
    }
}
