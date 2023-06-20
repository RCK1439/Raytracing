#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Timer.hpp"

#include <iostream>
#include <string>
#include <regex>
#include <vector>

struct Arguments
{
    u32         Width           = 1024;
    u32         Height          = 512;
    u32         NumberOfSamples = 32;
    u32         Depth           = 50;
    bool        ShowHelp        = false;
    std::string OutputPath      = "out/raytracing.png";
};

class ArgumentParser
{
public: 
    static Arguments Parse(const std::vector<std::string>& args)
    {
        const size_t size = args.size();

        Arguments settings;
        if (size == 0)
            return settings;

        for (size_t i = 0; i < size; i++)
        {
            const std::string& arg = args[i];

            if      (IsFlag(arg, "-[sS]")) i += ParseSize(settings, i, args) ? 2 : 0;
            else if (IsFlag(arg, "-[aA]")) i += (u32)ParseSamples(settings, i, args);
            else if (IsFlag(arg, "-[dD]")) i += (u32)ParseDepth(settings, i, args);
            else if (arg == "-o")          i += (u32)ParseOutput(settings, i, args);
            else if (arg == "-help")
            {
                settings.ShowHelp = true;
                return settings;
            }
        }

        return settings;
    }

private:
    static bool IsNumeric(const std::string& val)
    {
        return std::regex_match(val, std::regex("-?[0-9]+"));
    }

    static bool IsFlag(const std::string& arg, const std::string& expr)
    {
        return std::regex_match(arg, std::regex(expr));
    }

    static bool ParseSize(Arguments& settings, size_t i, const std::vector<std::string>& args)
    {
        if (i + 2 >= args.size())
            return false;

        if (IsNumeric(args[i + 1]) && IsNumeric(args[i + 2]))
        {
            settings.Width  = (u32)std::stoul(args[i + 1]);
            settings.Height = (u32)std::stoul(args[i + 2]);

            return true;
        }

        return false;
    }

    static bool ParseSamples(Arguments& settings, size_t i, const std::vector<std::string>& args)
    {
        if (i + 1 >= args.size())
            return false;

        if (IsNumeric(args[i + 1]))
        {
            settings.NumberOfSamples = (u32)std::stoul(args[i + 1]);
            return true;
        }

        return false;
    }

    static bool ParseDepth(Arguments& settings, size_t i, const std::vector<std::string>& args)
    {
        if (i + 1 >= args.size())
            return false;

        if (IsNumeric(args[i + 1]))
        {
            settings.Depth = (u32)std::stoul(args[i + 1]);
            return true;
        }

        return false;
    }

    static bool ParseOutput(Arguments& settings, size_t i, const std::vector<std::string>& args)
    {
        if (i + 1 >= args.size())
            return false;

        settings.OutputPath = args[i + 1];
        return true;
    }
};

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

    std::cout << "Dimensions: " << settings.Width << "x" << settings.Height << std::endl;
    std::cout << "Anti-aliasing samples: " << settings.NumberOfSamples << std::endl;
    std::cout << "Maximum bounce depth: " << settings.Depth << std::endl;

    rt::Scene scene;
    rt::Camera camera({ 13.0f, 2.0f, 3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 20.0f, (f32)settings.Width / (f32)settings.Height, 0.1f, 10.0f);

    rt::Renderer::Init(settings.Width, settings.Height, settings.NumberOfSamples, settings.Depth);

    Timer timer;

    timer.Start();
    rt::Renderer::Render(scene, camera);
    timer.Stop();

    rt::Renderer::Export(settings.OutputPath);

    return 0;
}