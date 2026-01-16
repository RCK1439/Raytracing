#pragma once

#include "Types.hpp"

#include "Error/BaseError.hpp"

namespace rt {

class ConfigError final : public BaseError
{
public:
    enum class Type : u8
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
    Type m_Type{};
};

struct Config
{
public:
    std::string OutputPath{"rtk.png"};
    u32         Width{1024};
    u32         Height{512};
    u32         NumberOfSamples{32};
    u32         Depth{50};
    bool        ShowHelp{};

public:
    static Result<Config, ConfigError> FromArgs(i32 argc, char* argv[]);
};

}
