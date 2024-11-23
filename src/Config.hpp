#pragma once

#include "Error/BaseError.hpp"

#include <cstdint>
#include <expected>

class ConfigError final : public BaseError
{
public:
    enum class Type
    {
        INVALID_DIMENSIONS_FORMAT,
        INVALID_SAMPLES_FORMAT,
        INVALID_DEPTH_FORMAT,
        INVALID_OUTPUT_FORMAT,
        INVALID_WIDTH,
        INVALID_HEIGHT,
        INVALID_NUM_SAMPLES,
        INVALID_DEPTH,
    };

public:
    ConfigError(Type type) :
        m_Type(type) {}

    std::string What() const override;

private:
    Type m_Type;
};

struct Config
{
public:
    uint32_t    Width           = 1024;
    uint32_t    Height          = 512;
    uint32_t    NumberOfSamples = 32;
    uint32_t    Depth           = 50;
    bool        ShowHelp        = false;
    std::string OutputPath      = "rtk.png";

public:
    static std::expected<Config, ConfigError> FromArgs(int32_t argc, char* argv[]);
};
