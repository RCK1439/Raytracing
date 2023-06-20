#pragma once

#include "Types.hpp"

#include <string>
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
    static Arguments Parse(const std::vector<std::string>& args);

private:
    static bool ParseSize(Arguments& settings, size_t i, const std::vector<std::string>& args);
    static bool ParseSamples(Arguments& settings, size_t i, const std::vector<std::string>& args);
    static bool ParseDepth(Arguments& settings, size_t i, const std::vector<std::string>& args);
    static bool ParseOutput(Arguments& settings, size_t i, const std::vector<std::string>& args);
};