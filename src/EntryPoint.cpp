/**
 * Ruan C. Keet (2023)
 * EntryPoint.cpp
*/

#include "ArgumentParser.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

#include <iostream>
#include <string>
#include <vector>

/**
 * \brief Entry point to the program.
 * 
 * \param argc  The amount of arguments passed in.
 * \param argv  The arguments passed from the command-line.
 * 
 * \return The exit status of the program.
*/
int main(int argc, char* argv[])
{
    std::vector<std::string> args;

    for (s32 i = 1; i < argc; i++)
        args.emplace_back(argv[i]);

    Arguments settings = ArgumentParser::Parse(args);
    if (settings.ShowHelp)
    {
        std::cout << "-----------Valid Arguments----------\n";
        std::cout << "-s or -S: Size of output image.            (e.g. -s 1280 720)\n";
        std::cout << "-a or -A: Number of anti-aliasing samples. (e.g. -a 32)\n";
        std::cout << "-d or -D: Depth of ray bounces.            (e.g. -d 8)\n";
        std::cout << "-o:       Output path for rendered image.  (e.g. -o path/on/disk/name.png)\n";
        std::cout << "-help:    Shows this dialog.               (e.g. -help)\n";

        return 0;
    }

    rt::Renderer::Init(settings.Width, settings.Height, settings.NumberOfSamples, settings.Depth);

    std::cout << "Dimensions: " << settings.Width << "x" << settings.Height << std::endl;
    std::cout << "Anti-aliasing samples: " << settings.NumberOfSamples << std::endl;
    std::cout << "Maximum bounce depth: " << settings.Depth << std::endl;

    Timer timer;

    rt::Scene scene;
    rt::Camera camera({ 13.0f, 2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 20.0f, (f32)settings.Width / (f32)settings.Height, 0.1f, 10.0f);

    timer.Start();
    rt::Renderer::Render(scene, camera);
    timer.Stop();

    rt::Renderer::Export(settings.OutputPath);
    
    return 0;
}