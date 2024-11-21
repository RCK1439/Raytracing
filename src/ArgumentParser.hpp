#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Arguments
{
    uint32_t    Width           = 1024;
    uint32_t    Height          = 512;
    uint32_t    NumberOfSamples = 32;
    uint32_t    Depth           = 50;
    bool        ShowHelp        = false;
    std::string OutputPath      = "rtk.png";
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
