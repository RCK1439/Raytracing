#pragma once

#include "Types.hpp"

#include <filesystem>
#include <ostream>
#include <sstream>

namespace rt {

struct Config
{
    std::filesystem::path OutputPath{"rtk.png"};
    u32                   Width{1024};
    u32                   Height{512};
    u32                   NumberOfSamples{32};
    u32                   Depth{50};
    bool                  ShowHelp{};
};

enum class ConfigParseError : u8
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

Result<Config, ConfigParseError> ParseConfig(i32 argc, char* argv[]);

std::ostream& operator<<(std::ostream& stream, ConfigParseError err);

}

template<>
struct std::formatter<rt::ConfigParseError>
{
    constexpr auto parse(std::format_parse_context& ctx) const
    {
        return ctx.begin();
    }

    auto format(const rt::ConfigParseError& err, std::format_context& ctx) const
    {
        std::stringstream stream;
        stream << err;

        return std::format_to(ctx.out(), "{}", stream.str());
    }
};
